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
            result = "for (" + i + ";" + i + "<" + parameters.front()  + ";++" + i + ")";
        }
    }

    return result;
}

bool polymorphic::blocks::block::evaulate(state &s)
{
    if(type == 0) return _if(s);
    else if(type == 1) return _loop(s);

    return false;
}

bool polymorphic::blocks::block::_if(state &s)
{
    if(type == 0)
    {
        if((variables.size() > 1)&&(parameters.size() >= 1))
        {
            vars::variable a = variables.front();
            vars::variable b = variables.back();

            std::string parameter = parameters.front();

            if(parameter == "<")
            {
                if((a.type == 0)&&(b.type == 0))
                {
                    std::string v1 = s.strings[a.id];
                    std::string v2 = s.strings[b.id];

                    return v1 < v2;
                }
                else if((a.type == 1)&&(b.type == 1))
                {
                    int v1 = s.integers[a.id];
                    int v2 = s.integers[b.id];

                    return v1 < v2;
                }
                else if((a.type == 2)&&(b.type == 2))
                {
                    int v1 = s.booleans[a.id];
                    int v2 = s.booleans[b.id];

                    return v1 < v2;
                }
            }  
            else if(parameter == ">")
            {
                 if((a.type == 0)&&(b.type == 0))
                {
                    std::string v1 = s.strings[a.id];
                    std::string v2 = s.strings[b.id];

                    return v1 > v2;
                }
                else if((a.type == 1)&&(b.type == 1))
                {
                    int v1 = s.integers[a.id];
                    int v2 = s.integers[b.id];

                    return v1 > v2;
                }
                else if((a.type == 2)&&(b.type == 2))
                {
                    int v1 = s.booleans[a.id];
                    int v2 = s.booleans[b.id];

                    return v1 > v2;
                }
            }
            else if(parameter == "<=")
            { if((a.type == 0)&&(b.type == 0))
                {
                    std::string v1 = s.strings[a.id];
                    std::string v2 = s.strings[b.id];

                    return v1 <= v2;
                }
                else if((a.type == 1)&&(b.type == 1))
                {
                    int v1 = s.integers[a.id];
                    int v2 = s.integers[b.id];

                    return v1 <= v2;
                }
                else if((a.type == 2)&&(b.type == 2))
                {
                    int v1 = s.booleans[a.id];
                    int v2 = s.booleans[b.id];

                    return v1 <= v2;
                }
            }
            else if(parameter == ">=")
            {
                if((a.type == 0)&&(b.type == 0))
                {
                    std::string v1 = s.strings[a.id];
                    std::string v2 = s.strings[b.id];

                    return v1 >= v2;
                }
                else if((a.type == 1)&&(b.type == 1))
                {
                    int v1 = s.integers[a.id];
                    int v2 = s.integers[b.id];

                    return v1 >= v2;
                }
                else if((a.type == 2)&&(b.type == 2))
                {
                    int v1 = s.booleans[a.id];
                    int v2 = s.booleans[b.id];

                    return v1 >= v2;
                }
            }
            else if(parameter == "==")
            {
                if((a.type == 0)&&(b.type == 0))
                {
                    std::string v1 = s.strings[a.id];
                    std::string v2 = s.strings[b.id];

                    return v1 == v2;
                }
                else if((a.type == 1)&&(b.type == 1))
                {
                    int v1 = s.integers[a.id];
                    int v2 = s.integers[b.id];

                    return v1 == v2;
                }
                else if((a.type == 2)&&(b.type == 2))
                {
                    int v1 = s.booleans[a.id];
                    int v2 = s.booleans[b.id];

                    return v1 == v2;
                }
            } 
        }
    }

    return false;
}

bool polymorphic::blocks::block::_loop(state &s)
{
    if(type == 1)
    {
        if((variables.size() > 0)&&(parameters.size() > 0))
        {
            vars::variable a = variables.front();
            int v1 = s.integers[a.id];

            std::string parameter = parameters.front();
            int v2 = std::atoi(parameter.c_str());

            bool result = (v1 + 1) < v2;
            s.integers[a.id] = v1 + 1;

           // if(v1 + 1 > 10000) return false;

            return result;
        }
    }

    return false;
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