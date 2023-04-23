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

std::tuple<std::string, bool, int, int> polymorphic::schema::run()
{		
    std::tuple<std::string, bool, int, int> output = data.run();

    int instr_counter = std::get<3>(output);
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
    }
    
    /*
    if(max_depth >= 8)//8)//3
    {
        std::cout << "max depth exceeded! (" << max_depth << ")\r\n";
        //scores.clear();
    }
    
    if(instr_counter > 50)//100)//200)
    {
        std::cout << "max instruction count exceeded! (" << instr_counter << ")\r\n";
        //scores.clear();
    }
*/
	return output;
}
