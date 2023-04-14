#include "population.h"
#include <iostream>

std::mt19937_64 polymorphic::population::generator(std::random_device{}());

void polymorphic::population::reset(settings::settings config, int size)
{
    init = false; cleanup();
    this->size = size;

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
    
    const float rate = 2.0f;
    const float mutation = (((float)size) / 100.0f) * rate;

    do
    {
        float total = 0.0f;
        best = 0.0f;
        
        for(int i = 0; i < size; ++i)
        {            
            schema s1 = *tournament(i);
            schema s2 = *tournament(i);

            schema temp = s1.cross(s2);

            //std::cout << temp.output();

            int t = (std::uniform_int_distribution<int>{0, size - 1})(generator);
            if(((float)t) <= mutation) 
            {
                data[i]->mutate();
            }

            std::string output = temp.run();

            if(temp.score() > data[i]->score()) *data[i] = temp;
            //*data[i] = temp;

            total += temp.score();//data[i]->score();
            if(temp.score() > best) 
            {
                best = temp.score();
                beststr = output;
            }
            if(temp.score() >= 0.9999f) result = true;
        }

        total /= size;

        std::cout << "Iteration (" << count << ") Best=" << best << " (" << beststr << ") Average=" << total << "\r\n";

        if((iterations > 0)&&(count > iterations)) result = true;

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
        if(data[i]->score() > s)
        {
            j = i;
            s = data[i]->score();
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
    schema *temp = NULL;

    int r2 = 0;
    
    do
    {
        r2 = (std::uniform_int_distribution<int>{0, (int(size)) - 1})(generator);
    } while(r2 != j);

    temp = data[r2];

    for(int i = 0; i < samples; ++i)
    {
        int r1 = 0;

        do
        {
            r1 = (std::uniform_int_distribution<int>{0, (int(size)) - 1})(generator);
        } while(r1 != j);

        if(data[r1]->score() > temp->score())
        {
            temp = data[r1];
        }
    }

    return temp;
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
}