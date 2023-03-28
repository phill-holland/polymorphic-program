#include "population.h"

std::mt19937_64 polymorphic::population::generator(std::random_device{}());

void polymorphic::population::reset(int size)
{
    init = false; cleanup();
    this->size = size;

    data = new polymorphic::schema*[size];
    if(data == NULL) return;

    for(int i = 0; i < size; ++i) { data[i] = NULL; }

    for(int i = 0; i < size; ++i) 
    { 
        data[i] = new polymorphic::schema();
        if(data[i] == NULL) return;
    }

    init = true;
}

/*
void polymorphic::population::start()
{
    generate();
    while(!iterate()) { };
}
*/

void polymorphic::population::generate()
{
    for(int i = 0; i < size; ++i)
    {
        data[i]->generate();
    }
}

/*
bool polymorphic::population::iterate()
{
    bool result = false;

    for(int i = 0; i < size; ++i)
    {            
        schema s1 = *tournament(i);
        schema s2 = *tournament(i);

        *data[i] = s1.cross(s2);

        int t = (std::uniform_int_distribution<int>{0, 100})(generator);
        if(t <= 10) data[i]->mutate();

        data[i]->run();

        if(data[i]->score() >= 1.0f) result = true;
    }

    return result;
}
*/

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

    for(int i = 0; i < samples; ++i)
    {
        int r1 = 0, r2 = 0;

        do
        {
            r1 = (std::uniform_int_distribution<int>{0, (int(size)) - 1})(generator);
            r2 = (std::uniform_int_distribution<int>{0, (int(size)) - 1})(generator);
        } while((r1 != j)&&(r2 != j));

        if(data[r1]->score() > data[r2]->score()) temp = data[r1];
        else temp = data[r2];
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