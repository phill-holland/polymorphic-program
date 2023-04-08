
#include "state.h"
#include <vector>

void polymorphic::state::reset(vars::variables &v)
{
    for(std::vector<polymorphic::vars::variable>::iterator it = v.values.begin(); it < v.values.end(); it++)
    {
        vars::variable v = *it;

        if(v.type == 0) strings[v.id] = std::string("");
        else if(v.type == 1) integers[v.id] = 0;
        else if(v.type == 2) booleans[v.id] = false;
    }
}