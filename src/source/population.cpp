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

polymorphic::schema polymorphic::population::go(int iterations)
{
    schema res;
    float most = 0.0f;

    bool result = false;
    int count = 0;

    const int max = 3;
    std::string outputs[max];
    
    const float mutate_rate_in_percent = 20.0f;
    const float mutation = (((float)size) / 100.0f) * mutate_rate_in_percent;

    do
    {
        int total_depth = 0;
        int total_instructions = 0;
        int mutants = 0;
        int overruns = 0;

        float total = 0.0f;        
      
        for(int generation = 0; generation < size; ++generation)
        {        
            std::tuple<std::string, bool, int, int> output;
            float sum = 0.0f;

            int offspring = worst();            
            schema temp;

            int t = (std::uniform_int_distribution<int>{0, size - 1})(generator);
            if(((float)t) <= mutation) 
            {
                schema *s1 = best(offspring);
                temp = *s1;

                temp.mutate();
                
                output = temp.run();
                set(offspring, temp);
                sum = temp.scores.sum();
                
                ++mutants;                
            }
            else
            {
                schema s1 = *best(offspring);
                schema s2 = *best(offspring);
                
                temp = s1.cross(s2);

                output = temp.run();
                set(offspring, temp);
                sum = temp.scores.sum();                
            }

            total += sum;
            total_depth += std::get<2>(output);
            total_instructions += std::get<3>(output);
            if(std::get<1>(output)) ++overruns;

            if(sum > most)
            {
                res = temp;
                most = sum;

                for(int f = 1; f < max; ++f)
                {
                    outputs[f] = outputs[f-1];
                }
                outputs[0] = std::get<0>(output);
            }

            if(sum >= 0.9999f) result = true;    
            if(std::get<0>(output)==std::string("hello world!")) result = true;            
        }

        total /= size;
        total_depth /= size;
        total_instructions /= size;

        std::cout << "Generation (" << count << ") Best=" << most << " (";
        for(int d = 0; d < max; ++d)
        {
            std::cout << outputs[d];
            if(d < max - 1) std::cout << ", ";
        }
        
        std::cout << ") Avg=" << total;
        std::cout << " AvgDep=" << total_depth << " AvgIns=" << total_instructions;
        std::cout << " Ovr=" << overruns;
        std::cout << " M=" << mutants << "\r\n";

        if((iterations > 0)&&(count > iterations)) result = true;

        //int c = getch();
        //if(c == 27) result = true;

        ++count;

    } while(!result);

    return res;
}

polymorphic::schema polymorphic::population::top()
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

polymorphic::schema *polymorphic::population::best(int j)
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

int polymorphic::population::worst()
{
    const int samples = 10;

	std::uniform_int_distribution<int> rand{ 0L, size - 1 };

    const int dimensions = polymorphic::score::length;

	dominance::kdtree::kdpoint temp1(dimensions), temp2(dimensions);
	dominance::kdtree::kdpoint origin(dimensions);

	temp1.set(0L);
	temp2.set(0L);
	origin.set(0L);

    int competition;

    int worst = rand(generator);
	float score = data[worst]->scores.sum();

	for (int i = 0; i < samples; ++i)
	{
		competition = rand(generator);

		for(int i = 0; i < dimensions; ++i)
		{
			float score1 = data[worst]->scores.scores[i];
			score1 = (score1 * ((float)maximum - minimum)) + minimum;

			temp1.set((long)score1, i);

			float score2 = data[competition]->scores.scores[i];
			score2 = (score2 * ((float)maximum - minimum)) + minimum;

			temp2.set((long)score2, i);
		}
					        
		float t2 = data[competition]->scores.sum();

		if(approximation->exists(temp2))
		{
			if(approximation->inside(temp2, &origin, &temp1))
			{
				score = t2;
			}
			else 
			{
				worst = competition;
				score = t2;
			}
		}
		else if(t2 < score)
		{
			worst = competition;
			score = t2;
		}
	}

	return worst;
}

bool polymorphic::population::set(int index, schema &source)
{
    std::uniform_real_distribution<float> dist{ 0.0f, 1.0f };
    bool result = false;

	if(source.scores.sum() < data[index]->scores.sum()) return false;

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
        result = true;
    }

    *data[index] = source;

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