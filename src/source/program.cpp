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

void polymorphic::program::mutate()
{
    if(variables.values.size() == 0) return;

// need to shuffle children order
// need to shuffle instruction order

// get run program to list used instructions
    std::vector<program*> p1 = deconstruct(*this);
    int a1 = (std::uniform_int_distribution<int>{0, (int)(p1.size() - 1)})(generator);
    int a2 = (std::uniform_int_distribution<int>{0, 2})(generator);
    //int a2 = 2;
    if(a2 == 0)
    {
        p1[a1]->block.mutate(configuration, variables);
    }
    else if(a2 == 1)
    {
        int s = p1[a1]->children.size();
        if(s > 0)
        {
            int d = (std::uniform_int_distribution<int>{0, (int)(s - 1)})(generator);   
            p1[a1]->children.erase(p1[a1]->children.begin() + d);
        }
        else p1[a1]->block.mutate(configuration, variables);
    }
/*    else if(a2 == 2)
    {
        program t(configuration);
        t.generate(variables, configuration._children.depth);
        p1[a1]->children.push_back(t);
    }
    */
    else if(a2 == 2)
    {
        p1[a1]->instructions.mutate(variables);
    }
}
/*
void polymorphic::program::mutant(polymorphic::program *source)
{
    const int c = 0;

    int t = (std::uniform_int_distribution<int>{0, 2})(generator);
    int chance = (std::uniform_int_distribution<int>{0, 50})(generator);

    block = source->block;
    instructions = source->instructions;

    if((chance == c)&&(t == 0)) block.mutate(source->configuration, variables);

    std::vector<polymorphic::program>::iterator it;

    for(it = source->children.begin(); it < source->children.end(); it++)
    {
        program p;
        p.mutant(&(*it));
        children.push_back(p);
    }
}
*/
void polymorphic::program::generate(vars::variables &v, int depth)
{
    if(depth > configuration._children.depth) return;

    instructions.generate(v);

    int length = (std::uniform_int_distribution<int>{0, configuration._children.max})(generator);
    
    for(int i = 0; i < length; ++i)
    {
        program temp(configuration);
        temp.block.type = (std::uniform_int_distribution<int>{0, 1})(generator);
        //temp.block.type = 0;

        if((temp.block.type == 0)&&(!v.isempty()))
        {
            vars::variable a;
            vars::variable b;

            int counter = 0;
            do
            {
                a = v.pick();
                b = v.pick(a.type);
            }while((counter++ < 10)&&(a.id==b.id));

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
            
            int k = (std::uniform_int_distribution<int>{configuration._loop.min, configuration._loop.max})(generator);

            temp.block.variables.push_back(a);
            temp.block.parameters.push_back(std::to_string(k));
        }

        temp.generate(v, depth + 1);
        children.push_back(temp);        
    }
}

std::tuple<std::string, bool, int, int> polymorphic::program::run()
{
    state s(variables);

    int instr_counter = 0;  
    std::string result;
    
    for(std::vector<polymorphic::instrs::instruction>::iterator it = instructions.values.begin(); it < instructions.values.end(); it++)
    {
        instrs::instruction in = *it;
        result += in.run(s);

        ++instr_counter;
    }
    
    std::vector<polymorphic::program>::iterator it;
    
    bool overrun = false;
    int max_depth = 0;
    
    for(it = children.begin(); it < children.end(); it++)
    {                    
        result += it->run(s, overrun, 0, max_depth, instr_counter);
    }

    return std::tuple<std::string, bool, int, int>(result, overrun, max_depth, instr_counter);
}

std::string polymorphic::program::run(state &s, bool &overrun, int depth, int &max_depth, int &instr_counter)
{    
    std::string result; 

    if(depth > max_depth) max_depth = depth;

    if(block.type == 0)
    {
        if(block._if(s))
        {
            for(std::vector<polymorphic::instrs::instruction>::iterator it = instructions.values.begin(); it < instructions.values.end(); it++)
            {
                instrs::instruction in = *it;
                result += in.run(s);

                ++instr_counter;
            }
            
            std::vector<polymorphic::program>::iterator it;

            for(it = children.begin(); it < children.end(); it++)
            {                    
                result += it->run(s, overrun, depth + 1, max_depth, instr_counter);
            }
        }
    }
    else if(block.type == 1)
    {
        int counter = 0;
        while((block._loop(s))&&(counter < OVERRUN))
        {
            for(std::vector<polymorphic::instrs::instruction>::iterator it = instructions.values.begin(); it < instructions.values.end(); it++)
            {
                instrs::instruction in = *it;
                result += in.run(s);

                ++instr_counter;
            }
            
            std::vector<polymorphic::program>::iterator it;

            for(it = children.begin(); it < children.end(); it++)
            {                    
                result += it->run(s, overrun, depth + 1, max_depth, instr_counter);
            }
            ++counter;
        };

        if(counter >= OVERRUN) overrun = true;
    }

    return result;
}

polymorphic::program polymorphic::program::unused()
{
    program result;

    std::unordered_map<int, std::tuple<polymorphic::vars::variable,int>> map;
    this->unique(map, result.variables, true);

    result.copy(this, NULL, map);

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

polymorphic::program polymorphic::program::cross(program &a, program &b, int c1, int c2)
{
    program result;

    std::vector<program*> p1 = deconstruct(a);
    std::vector<program*> p2 = deconstruct(b);

    int a1 = (std::uniform_int_distribution<int>{0, (int)(p1.size() - 1)})(generator);
    int b1 = (std::uniform_int_distribution<int>{0, (int)(p2.size() - 1)})(generator);

    if((c1 >= 0)&&(c1 < p1.size()))
        a1 = c1;

    if((c2 >= 0)&&(c2 < p2.size()))
        b1 = c2;

    int e1 = p2.size() - 1;
    if(b1 < p2.size() - 1) e1 = (std::uniform_int_distribution<int>{b1, (int)(p2.size() - 1)})(generator);

    result.variables = a.variables;

    std::unordered_map<int, std::tuple<polymorphic::vars::variable,int>> map;
    p2[b1]->unique(map, result.variables);

    //result.copy(&a, p1[a1], NULL, p2[b1], map);
    result.copy(&a, p1[a1], p2[e1], p2[b1], map);
 
    return result.unused();
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

void polymorphic::program::copy(program *source, program *until, program *end,
                                polymorphic::program *alt_source, 
                                std::unordered_map<int, std::tuple<vars::variable,int>> &result)
{
    if(source != until)
    {
        block = source->block;
        instructions = source->instructions;

        std::vector<polymorphic::program>::iterator it;

        for(it = source->children.begin(); it < source->children.end(); it++)
        {
            program p;
            p.copy(&(*it), until, end, alt_source, result);
            children.push_back(p);            
        }
    }
    else
    {
        this->copy(alt_source, end, result);     
    }
}

void polymorphic::program::copy(polymorphic::program *source, polymorphic::program *end, std::unordered_map<int, std::tuple<vars::variable,int>> &result)
{
    if(end != NULL)
    {
        if(end == source) return;
    }

    block.copy(source->block, result);
    instructions.copy(source->instructions, result);

    std::vector<polymorphic::program>::iterator it;

    for(it = source->children.begin(); it < source->children.end(); it++)
    {
        if((it->children.size() != 0)&&(it->instructions.values.size() != 0))
        {
            program p;
            p.copy(&(*it), end, result);
            children.push_back(p);
        }
    }
}

void polymorphic::program::unique(std::unordered_map<int, std::tuple<vars::variable,int>> &result, vars::variables &input, bool ignore_assignments)
{
    std::unordered_map<int, vars::variable> map;
    
    for(std::vector<polymorphic::vars::variable>::iterator it = block.variables.begin(); it < block.variables.end(); it++)
    {
        vars::variable v = *it;
        if(map.find(v.id) == map.end()) map[v.id] = v;
    }

    if(ignore_assignments)
    {
        for(std::vector<polymorphic::instrs::instruction>::iterator it = instructions.values.begin(); it < instructions.values.end(); it++)
        {
            int count = 0;
            for(std::vector<polymorphic::vars::variable>::iterator jt = it->variables.begin(); jt < it->variables.end(); jt++)
            {
                if((count == 0)&&((it->type==0)||(it->type==1)))
                {
                }
                else
                {
                    vars::variable v = *jt;
                    if(map.find(v.id) == map.end()) map[v.id] = v;
                }

                ++count;
            }
        }
    }
    else
    {
        for(std::vector<polymorphic::instrs::instruction>::iterator it = instructions.values.begin(); it < instructions.values.end(); it++)
        {
            for(std::vector<polymorphic::vars::variable>::iterator jt = it->variables.begin(); jt < it->variables.end(); jt++)
            {
                vars::variable v = *jt;
                if(map.find(v.id) == map.end()) map[v.id] = v;
            }
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