#include "program.h"
#include <stack>
#include <unordered_map>
#include <iostream>

std::mt19937_64 polymorphic::program::generator(std::random_device{}());

void polymorphic::program::clear()
{    
    block.clear();
    variables.clear();
    instructions.clear();
    children.clear();
}

void polymorphic::program::generate()
{
    variables.generate();
    generate(variables, 0);
}

void polymorphic::program::generate(vars::variables &v, int depth)
{
    if(depth > configuration._children.depth) return;

    instructions.generate(v);

    int length = (std::uniform_int_distribution<int>{0, configuration._children.max})(generator);
    
    for(int i = 0; i < length; ++i)
    {
        program temp(configuration);
        temp.block.type = (std::uniform_int_distribution<int>{0, 1})(generator);

        if((temp.block.type == 0)&&(!v.isempty()))
        {
            vars::variable a = v.pick();
            vars::variable b = v.pick(a.type);

            temp.block.variables.push_back(a);
            temp.block.variables.push_back(b);


            int k = (std::uniform_int_distribution<int>{0, 4})(generator);
            std::string _operator;

            if(k == 0) _operator = "<";
            else if(k == 1) _operator += ">";
            else if(k == 2) _operator += "<=";
            else if(k == 3) _operator += ">=";
            else _operator += "==";

            temp.block.parameters.push_back(_operator);
        }
        else if(temp.block.type == 1)
        {
            vars::variable a = v.pick(1);
            if(a.type != 1) a = v.get(1);
            //vars::variable a = v.local(1);
            
            int k = (std::uniform_int_distribution<int>{0, configuration._loop.max})(generator);

            temp.block.variables.push_back(a);
            temp.block.parameters.push_back(std::to_string(k));
        }

        temp.generate(v, depth + 1);
        children.push_back(temp);        
    }
}

std::string polymorphic::program::run()
{
    state s(variables);
    std::string result;

     for(std::vector<polymorphic::instrs::instruction>::iterator it = instructions.values.begin(); it < instructions.values.end(); it++)
    {
        instrs::instruction in = *it;
        result += in.run(s);
    }
    
    std::vector<polymorphic::program>::iterator it;

    for(it = children.begin(); it < children.end(); it++)
    {                    
        result += it->run(s,0);
    }

    return result;
}

std::string polymorphic::program::run(state &s, int iterations)
{    
    std::string result; 
    if(iterations > 10000) return result;

    if(block.type == 0)
    {
        if(block._if(s))
        {
            for(std::vector<polymorphic::instrs::instruction>::iterator it = instructions.values.begin(); it < instructions.values.end(); it++)
            {
                instrs::instruction in = *it;
                result += in.run(s);
            }
            
            std::vector<polymorphic::program>::iterator it;

            for(it = children.begin(); it < children.end(); it++)
            {                    
                result += it->run(s, iterations + 1);
            }
        }
    }
    else if(block.type == 1)
    {
        while(block._loop(s))
        {
            for(std::vector<polymorphic::instrs::instruction>::iterator it = instructions.values.begin(); it < instructions.values.end(); it++)
            {
                instrs::instruction in = *it;
                result += in.run(s);
            }
            
            std::vector<polymorphic::program>::iterator it;

            for(it = children.begin(); it < children.end(); it++)
            {                    
                result += it->run(s, iterations + 1);
            }
        };
    }

    return result;
}

std::string polymorphic::program::output()
{
    std::string result;

    result = "#include <iostream>\nusing namespace std;\n int main() {";
    result += get(0);
    result += "return 0;\n}\n";
    
    return result;
}

polymorphic::program polymorphic::program::cross(program &a, program &b)
{
    program result;

    std::vector<program*> p1 = deconstruct(a);
    std::vector<program*> p2 = deconstruct(b);

    int a1 = (std::uniform_int_distribution<int>{0, (int)(p1.size() - 1)})(generator);
    int b1 = (std::uniform_int_distribution<int>{0, (int)(p2.size() - 1)})(generator);

    result.variables = a.variables;

    std::unordered_map<int, std::tuple<polymorphic::vars::variable,int>> map;
    p2[b1]->unique(map, result.variables);

    program *crossover = result.copy(&a, p1[a1]);
    if(crossover != NULL) crossover->copy(p2[b1], map);
    else std::cout << "crossover is null!\r\n";

    return result;
}

std::vector<polymorphic::program*> polymorphic::program::deconstruct(polymorphic::program &a)
{
    std::stack<program*> stack;
    std::vector<program*> result;

    stack.push(&a);

    while(!stack.empty())
    {
        program *t = stack.top();
        stack.pop();

        result.push_back(t);

        std::vector<polymorphic::program>::iterator it;

        for(it = t->children.begin(); it < t->children.end(); it++)
        {                    
            stack.push(&(*it));
        }
    }

    return result;
}

polymorphic::program *polymorphic::program::copy(program *source, program *until)
{
    if(source != until)
    {
        block = source->block;
        instructions = source->instructions;

        std::vector<polymorphic::program>::iterator it;

        for(it = source->children.begin(); it < source->children.end(); it++)
        {
            program p;
            p.copy(&(*it), until);
            children.push_back(p);
        }
    }
    else return this;

    return NULL;
}

void polymorphic::program::copy(polymorphic::program *source, std::unordered_map<int, std::tuple<vars::variable,int>> &result)
{
    block.copy(source->block, result);
    instructions.copy(source->instructions, result);

    std::vector<polymorphic::program>::iterator it;

    for(it = source->children.begin(); it < source->children.end(); it++)
    {
        program p;
        p.copy(&(*it), result);
        children.push_back(p);
    }
}

std::unordered_map<int, std::tuple<polymorphic::vars::variable,int>> polymorphic::program::unique(std::unordered_map<int, std::tuple<vars::variable,int>> &result, vars::variables &input)
{
    std::unordered_map<int, vars::variable> map;
    
    std::vector<polymorphic::vars::variable> v_it;

    for(std::vector<polymorphic::vars::variable>::iterator it = block.variables.begin(); it < block.variables.end(); it++)
    {
        vars::variable v = *it;
        if(map.find(v.id) == map.end()) map[v.id] = v;
    }

    for(std::vector<polymorphic::instrs::instruction>::iterator it = instructions.values.begin(); it < instructions.values.end(); it++)
    {
        for(std::vector<polymorphic::vars::variable>::iterator jt = it->variables.begin(); jt < it->variables.end(); jt++)
        {
            vars::variable v = *jt;
            if(map.find(v.id) == map.end()) map[v.id] = v;
        }
    }

    for(std::vector<polymorphic::program>::iterator it = children.begin(); it < children.end(); it++)
    {
        it->unique(result, input);
    }

    for(auto& a: map)
    {
        if(result.find(a.first) == result.end())
        {
            vars::variable w = a.second;
            vars::variable n = input.get(w.type);

            result[a.first] = std::tuple<vars::variable,int>(w,n.id);
        }
    }

    return result;
}

std::string polymorphic::program::get(int depth)
{    
    /*
	auto tabs = [](int depth) 
	{ 
		std::string result;

        for(int i = 0; i < depth; ++i)
        {
            result += "\t";
        }

        return result;
	};
    */

    std::string result;

    result += block.declare(variables) + "{\n";
    result += variables.declare();
    result += instructions.declare(variables);
    
    for(std::vector<polymorphic::program>::iterator it = children.begin(); it < children.end(); it++)
    {        
        program b = *it;
        result += b.get(depth + 1);
    }

    result += "}\n";

    return result;
}