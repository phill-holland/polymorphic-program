#include "variables.h"

std::mt19937_64 polymorphic::vars::variables::generator(std::random_device{}());

void polymorphic::vars::variables::clear() 
{ 
    values.clear(); 
    idx = 0;
}

void polymorphic::vars::variables::generate()
{
    clear();

    int vars = (std::uniform_int_distribution<int>{min, max})(generator);
    for(int i = 0; i < vars; ++i)
    {
        get();
    }
}
            
std::string polymorphic::vars::variables::name(polymorphic::vars::variable &v)
{
    std::string result;
    int t = (int)v.id; 

    do
    {
        char c = (char)(t % 26);
        result += (c + 97);
        t -= 26;
    }while(t > 26);

    if(t > 0) result += (char)(t + 97);

    return result;
}

std::string polymorphic::vars::variables::declare()
{
    std::string result;

    for(std::vector<polymorphic::vars::variable>::iterator it = values.begin(); it < values.end(); it++)
    {
        variable v = *it;
    
        //if(!v.is_local)
        //{
            if(v.type == 0) result += "string " + name(v) + ";\n";
            else if(v.type == 1) result += "int " + name(v) + ";\n";
            else if(v.type == 2) result += "bool " + name(v) +";\n";
        //}

    }

    return result;
}

polymorphic::vars::variable polymorphic::vars::variables::get()
{
    variable temp;

    temp.id = inc();
    temp.type = (std::uniform_int_distribution<int>{0, 2})(generator); 
    //temp.is_local = false;

    values.push_back(temp);

    return temp;
}

polymorphic::vars::variable polymorphic::vars::variables::get(int type)
{
    variable temp;

    temp.id = inc();
    temp.type = type;
    //temp.is_local = false;

    values.push_back(temp);

    return temp;
}
/*
polymorphic::vars::variable polymorphic::vars::variables::local(int type)
{
    variable temp;

    temp.id = inc();
    temp.type = type;
    temp.is_local = true;

    values.push_back(temp);

    return temp;
}
*/
polymorphic::vars::variable polymorphic::vars::variables::pick()
{
    int counter = 0;
    while(true) 
    {
        int i = (std::uniform_int_distribution<int>{0, ((int)values.size()) - 1})(generator);
        variable v = values[i];

        if(counter > 20) return values[i];

        ++counter;
    };

    //int i = (std::uniform_int_distribution<int>{0, ((int)values.size()) - 1})(generator);
    //return values[0];    
    //return get();
}

polymorphic::vars::variable polymorphic::vars::variables::pick(int type)
{
    int counter = 0;
    while(true) 
    {
        int i = (std::uniform_int_distribution<int>{0, ((int)values.size()) - 1})(generator);
        variable v = values[i];

        if((v.type == type)||(counter > 20)) return values[i];

        ++counter;
    };

    //return get(type);//values[0];
}
