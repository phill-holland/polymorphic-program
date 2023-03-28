#include "schema.h"

std::mt19937_64 polymorphic::schema::generator(std::random_device{}());

void polymorphic::schema::reset()
{
    _score = 0.0f;
}

void polymorphic::schema::generate()
{
    data.clear();
    data.generate();
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
    /*
    std::string result;

    for(int i = 0; i < data.size(); ++i)
    {
        result += grammar->get(data[i]);
    }

    // score here, using parsercpp - and general rules
    // does it contain hello world?

    _score = 0.0f;
    */
}