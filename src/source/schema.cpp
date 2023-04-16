#include "schema.h"
#include <iostream>
#include <tuple>

std::mt19937_64 polymorphic::schema::generator(std::random_device{}());

void polymorphic::schema::reset()
{
    scores.clear();
}

void polymorphic::schema::generate()
{
    data.clear();
    data.generate();
}

void polymorphic::schema::mutate()
{
	data.mutate();
}

polymorphic::schema polymorphic::schema::cross(schema &value)
{
    program p = data.cross(data, value.data);
    return schema(p);
}

std::string polymorphic::schema::run()
{		
    std::tuple<std::string, bool, int> output = data.run();

    int max_depth = std::get<2>(output);
    bool overrun = std::get<1>(output);    
    std::string value = std::get<0>(output);

    if(!overrun)
    {        
        scores.compute(value);
    } 
    else 
    {
        scores.clear();
        std::cout << "overrun!\r\n";
    }
    
    if(max_depth >= 8)
    {
        std::cout << "max depth exceeded! (" << max_depth << ")\r\n";
    }
    

	return value;
}
