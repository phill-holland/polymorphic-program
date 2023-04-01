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
