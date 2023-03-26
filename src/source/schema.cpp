#include "schema.h"

std::mt19937_64 polymorphic::schema::generator(std::random_device{}());

void polymorphic::schema::reset(templates::grammar *g, int min, int max)
{
    grammar = g;

    _min = min;
    _max = max;

    _score = 0.0f;
}

void polymorphic::schema::generate()
{
    data.clear();

    int r = (std::uniform_int_distribution<int>{_min, _max})(generator);    

    for(int i = 0; i < r; ++i)
    {
        int e = (std::uniform_int_distribution<int>{0, grammar->length()})(generator);
        data.push_back(e);
    }
}

void polymorphic::schema::mutate()
{
}

polymorphic::schema polymorphic::schema::cross(schema &value)
{
    return (*this);
}

void polymorphic::schema::run()
{
    std::string result;

    for(int i = 0; i < data.size(); ++i)
    {
        result += grammar->get(data[i]);
    }

    // score here, using parsercpp - and general rules
    // does it contain hello world?

    _score = 0.0f;
}