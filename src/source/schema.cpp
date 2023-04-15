#include "schema.h"

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
    std::string output = data.run();
	scores.compute(output);	
	return output;
}
