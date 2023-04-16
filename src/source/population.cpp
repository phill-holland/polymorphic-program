#include "population.h"
#include <iostream>
#include <fcntl.h>

std::mt19937_64 polymorphic::population::generator(std::random_device{}());

void polymorphic::population::reset(settings::settings config, int size)
{
    init = false; cleanup();
    this->size = size;

	approximation = new dominance::kdtree::kdtree(polymorphic::score::length, 10000);
	if (approximation == NULL) return;
	if (!approximation->initalised()) return;

    data = new polymorphic::schema*[size];
    if(data == NULL) return;

    for(int i = 0; i < size; ++i) { data[i] = NULL; }

    for(int i = 0; i < size; ++i) 
    { 
        data[i] = new polymorphic::schema(config);
        if(data[i] == NULL) return;
    }

    init = true;
}

void polymorphic::population::generate()
{
    for(int i = 0; i < size; ++i)
    {
        data[i]->generate();
    }
}

bool polymorphic::population::go(int iterations)
{
    bool result = false;
    int count = 0;

    std::string beststr;
    float best = 0.0f;
    
    const float mutate_rate_in_percent = 20.0f;
    const float mutation = (((float)size) / 100.0f) * mutate_rate_in_percent;

    do
    {
        float total = 0.0f;
        best = 0.0f;

        for(int i = 0; i < size; ++i)
        {            
            int t = (std::uniform_int_distribution<int>{0, size - 1})(generator);
            if(((float)t) <= mutation) 
            {
                data[i]->mutate();
            }
        }
        
        for(int i = 0; i < size; ++i)
        {            
            schema s1 = *tournament(i);
            schema s2 = *tournament(i);

            schema temp = s1.cross(s2);

            //std::cout << temp.output();

            std::string output = temp.run();
            float sum = temp.scores.sum();

            if(set(i, temp))
            {                
                if(sum > best)
                {
                    best = sum;
                    beststr = output;
                }
                if(sum >= 0.9999f) result = true;                
            }

            total += sum;
        }

        total /= size;

        std::cout << "Iteration (" << count << ") Best=" << best << " (" << beststr << ") Average=" << total << "\r\n";

        if((iterations > 0)&&(count > iterations)) result = true;

        int c = getch();
        if(c == 27) result = true;

        ++count;

    } while(!result);

    return result;
}

polymorphic::schema polymorphic::population::best()
{
    float s = 0.0f;
    int j = 0;

    for(int i = 0; i < size; ++i)
    {
        if(data[i]->scores.sum() > s)
        {
            j = i;
            s = data[i]->scores.sum();
        }

    }

    return *data[j];
}

std::string polymorphic::population::output()
{
    std::string result;

    for(int i = 0; i < size; ++i)
    {
        result += data[i]->output();
    }

    return result;
}

polymorphic::schema *polymorphic::population::tournament(int j)
{
    const int samples = 10;

	std::uniform_int_distribution<int> rand{ 0, size - 1 };

    const int dimensions = polymorphic::score::length;

	dominance::kdtree::kdpoint temp1(dimensions), temp2(dimensions);
	dominance::kdtree::kdpoint origin(dimensions);

	temp1.set(0L);
	temp2.set(0L);
	origin.set(0L);

    long competition;

    long best = rand(generator);
	float score = data[best]->scores.sum();

	for (int i = 0; i < samples; ++i)
	{
		competition = rand(generator);

		for(int i = 0; i < dimensions; ++i)
		{
			float score1 = data[best]->scores.scores[i];
			score1 = (score1 * ((float)maximum - minimum)) + minimum;

			temp1.set((long)score1, i);

			float score2 = data[competition]->scores.scores[i];
			score2 = (score2 * ((float)maximum - minimum)) + minimum;

			temp2.set((long)score2, i);
		}
		
		float t2 = data[competition]->scores.sum();

		if(approximation->exists(temp1))
		{
			if(approximation->inside(temp1, &origin, &temp2))
			{
				score = t2;
			}
			else
			{
				best = competition;
				score = t2;
			}
		}
        else if(t2 > score)
		{
			best = competition;
			score = t2;
		}
	}

	return data[best];
}

bool polymorphic::population::set(int index, schema &source)
{
    std::uniform_real_distribution<float> dist{ 0.0f, 1.0f };
    bool result = false;

	//core::threading::semaphore lock(token);
	
	//long offspring = worst(); // input from parameters
	//if(source.score < schemas[offspring]->score) return offspring;

    const int dimensions = polymorphic::score::length;

	dominance::kdtree::kdpoint temp1(dimensions), temp2(dimensions);

	temp1.set(0L);
	temp2.set(0L);

	for(long i = 0L; i < dimensions; ++i)
	{
		float score1 = data[index]->scores.scores[i];
		score1 = (score1 * ((float)maximum - minimum)) + minimum;

		temp1.set((long)score1, i);

		float score2 = source.scores.scores[i];
		score2 = (score2 * ((float)maximum - minimum)) + minimum;

		temp2.set((long)score2, i);
	}

	if(!temp1.issame(minimum)) 
	{
		if(approximation->exists(temp2))
		{
			approximation->remove(temp1);
		}
	}
	if(!temp2.issame(minimum)) 
    {
        approximation->insert(&temp2);
        *data[index] = source;
        result = true;
    }

    //*data[index] = source;

	return result;
}

int polymorphic::population::getch() 
{ 
    int ch; 

    int flags = fcntl(0, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(0, F_SETFL, flags);    
    ch = getchar(); 

    return ch; 
} 

void polymorphic::population::makeNull() 
{ 
    approximation = NULL;
    data = NULL; 
}

void polymorphic::population::cleanup() 
{ 
    if(data != NULL)
    {
        for(int i = size - 1; i >= 0; i--)
        {
            if(data[i] != NULL) delete data[i];
        }

        delete[] data;
    }

    if(approximation != NULL) delete approximation;    
}