#include "blocks.h"

std::string polymorphic::blocks::block::declare(vars::variables &vars)
{
    std::string result;

    if(type == 0)
    {
        if((variables.size() > 1)&&(parameters.size() >= 1))
        {
            result = "if (" + vars.name(variables.front());
            result += parameters.front();
            result += vars.name(variables.back()) + ")";     
        }
    }
    else if(type == 1)
    {
        if((variables.size() > 0)&&(parameters.size() > 0))
        {
            std::string i = vars.name(variables.front());
            result = "for (int " + i + "=0;" + i + "<" + parameters.front()  + ";++" + i + ")";
        }
    }

    return result;
}


void polymorphic::blocks::block::copy(block &source, std::unordered_map<int, std::tuple<vars::variable,int>> map)
{
    std::vector<polymorphic::vars::variable>::iterator it;
    
    for(it = source.variables.begin(); it < source.variables.end(); it++)
    {
        vars::variable temp;
        vars::variable v = *it;

        temp.id = std::get<1>(map[v.id]);
        temp.type = v.type;
        
        variables.push_back(temp);
    }

    parameters = source.parameters;
}