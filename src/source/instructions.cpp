#include "instructions.h"

std::mt19937_64 polymorphic::instrs::instruction::generator(std::random_device{}());

std::string polymorphic::instrs::instruction::run(state &s)
{
    if(type == 0)
    {        
        // assign one variable to another

        vars::variable a = variables.front();
        vars::variable b = variables.back();

        if((a.type == 0)&&(b.type == 0))
        {
            s.strings[a.id] = s.strings[b.id];
        }
        else if((a.type == 1)&&(b.type == 1))
        {
            s.integers[a.id] = s.integers[b.id];
        }
        else if((a.type == 2)&&(b.type == 2))
        {
            s.booleans[a.id] = s.booleans[b.id];
        }
    }
    else if (type == 1)
    {
        // set variable to const

        vars::variable a = variables.front();
        std::string parameter = parameters.front();

        if(a.type == 0)
        {
            s.strings[a.id] = parameter;
        }
        else if(a.type == 1)
        {
            s.integers[a.id] = std::atoi(parameter.c_str());
        }
        else if(a.type == 2)
        {
            s.booleans[a.id] = (parameter == "true" ? true : false);
        }
    }
    else if (type == 2)
    {
        // output to result

        vars::variable a = variables.front();

        if(a.type == 0)
        {
            return s.strings[a.id];
        }
        else if(a.type == 1)
        {
            return std::to_string(s.integers[a.id]);
        }
        else if(a.type == 2)
        {
            return std::to_string(s.booleans[a.id]);
        }
    }

    return std::string("");
}

void polymorphic::instrs::instruction::mutate(vars::variables &variables)
{    
    generate(variables, type);    
}

void polymorphic::instrs::instruction::generate(vars::variables &variables)
{
    int type = 0;
    int counter = 0;

    do
    { 
        type = (std::uniform_int_distribution<int>{0, 2})(generator); 
        ++counter; 
    }while((!generate(variables, type))&&(counter<20));
}

bool polymorphic::instrs::instruction::generate(vars::variables &variables, int type)
{
    instruction temp;
    temp.type = type;

    if(temp.type == 0)
    {
        vars::variable a;
        vars::variable b;

        int counter = 0;
        do
        {
            a = variables.pick();
            b = variables.pick(a.type);
        }while((counter++ < 10)&&(a.id==b.id));

        temp.variables.push_back(a);
        temp.variables.push_back(b);
    }
    else if(temp.type == 1)
    {
        vars::variable a = variables.pick();

        if(a.type == 0) // string
        {
            // random string

            std::string alphabet[] = { "he", "ll", "o ", "wo", "rl", "d!" }; // 5
            std::string s;
            
            int k = (std::uniform_int_distribution<int>{0, 5})(generator);
            s = alphabet[k];
            
            /*
            std::string alphabet[] = { "hello ", "world!" }; // 5
            std::string s;
            
            int k = (std::uniform_int_distribution<int>{0, 1})(generator);
            s = alphabet[k];
            */

/*
            std::string alphabet[] = { "h", "e", "l", "o ", "w", "r", "d", "!", " " }; // 5
            std::string s;
            
            //int k = (std::uniform_int_distribution<int>{0, 5})(generator);                    
            int k = 1;
            for(int i = 0; i < k; ++i)
            {
                int y = (std::uniform_int_distribution<int>{0, 8})(generator);
                s += alphabet[y];
            }
  */          
            //s = alphabet[k];

            /*
            std::string s;
            int k = (std::uniform_int_distribution<int>{0, 10})(generator);
            for(int i = 0; i < k; ++i)
            {
                int y = (std::uniform_int_distribution<int>{97, 122})(generator);
                s += (char)y;
            }
            */

            temp.variables.push_back(a);
            temp.parameters.push_back(s);
        }
        else if(a.type == 1) // int
        {
            int k = (std::uniform_int_distribution<int>{0, 100})(generator);

            temp.variables.push_back(a);
            temp.parameters.push_back(std::to_string(k));
        }
        else if(a.type == 2) // bool
        {
            int k = (std::uniform_int_distribution<int>{0, 1})(generator);
            
            temp.variables.push_back(a);
            temp.parameters.push_back(std::string((k == 0 ? "true" : "false")));
        }
    }
    else if(temp.type == 2)// cout variable
    {
        vars::variable a = variables.pick(0);
        if(a.type == 0) temp.variables.push_back(a);
        else return false;
    }

    *this = temp;       

    return true;
}

std::mt19937_64 polymorphic::instrs::instructions::generator(std::random_device{}());

void polymorphic::instrs::instructions::mutate(vars::variables &variables)
{
    if(values.size() > 0)
    {
        int j = (std::uniform_int_distribution<int>{0, (int)(values.size() - 1)})(generator);
        int t = (std::uniform_int_distribution<int>{0, 1})(generator);

        if(t == 0) values[j].mutate(variables);
        else values.erase(values.begin() + j);
    }
    else
    {
        instruction temp;

        temp.generate(variables);
        values.push_back(temp);        
    }
}

void polymorphic::instrs::instructions::generate(vars::variables &variables)
{
    clear();

    if(!variables.isempty())
    {
        int instrs = (std::uniform_int_distribution<int>{min, max})(generator);
        for(int i = 0; i < instrs; ++i)
        {
            instruction temp;

            temp.generate(variables);
            values.push_back(temp);        
        }
    }
}
    
std::string polymorphic::instrs::instructions::declare(vars::variables &variables)
{
    std::string result;

    for(std::vector<polymorphic::instrs::instruction>::iterator it = values.begin(); it < values.end(); it++)
    {
        instruction in = *it;

        if(in.type == 0)
        {
            result += variables.name(in.variables.front()) + "=" + variables.name(in.variables.back()) + ";\n";
        }
        else if(in.type == 1)
        {
            vars::variable v = in.variables.front();
            if(v.type == 0) result += variables.name(v) + "=\"" + in.parameters.front() + "\";\n"; 
            else result += variables.name(v) + "=" + in.parameters.front() + ";\n"; 
        }
        else if(in.type == 2)
        {
            result += "cout << " + variables.name(in.variables.front()) + ";\n";
        }
    }

    return result;
}    

void polymorphic::instrs::instructions::copy(instructions &source, std::unordered_map<int, std::tuple<vars::variable,int>> map)
{
    for(std::vector<polymorphic::instrs::instruction>::iterator it = source.values.begin(); it < source.values.end(); it++)
    {
        instruction s = *it;
        instruction temp;

        temp.type = s.type;
        temp.parameters = s.parameters;

        bool excluded = false;

        vars::variable previous;

        for(std::vector<polymorphic::vars::variable>::iterator jt = s.variables.begin(); jt < s.variables.end(); jt++)
        {            
            vars::variable v = *jt;
            
            if(map.find(v.id) != map.end())
            {
                vars::variable t;
                t.id = std::get<1>(map[v.id]);
                t.type = v.type;
                temp.variables.push_back(t);
            }
            else excluded = true;

            if((s.type == 0)&&(previous.id == v.id)&&(previous.type == v.type)) excluded = true;

            previous = *jt;
        }
        
        if(!excluded) 
        {
            values.push_back(temp);        
        }
    }
}