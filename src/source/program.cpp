#include "program.h"
#include <stack>

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
    if(depth > 5) return;

    instructions.generate(v);

    int length = (std::uniform_int_distribution<int>{0, 5})(generator);
    
    for(int i = 0; i < length; ++i)
    {
        program temp;
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
            if(a.type == 1)
            {
                int k = (std::uniform_int_distribution<int>{0, 20})(generator);

                temp.block.variables.push_back(a);
                temp.block.parameters.push_back(std::to_string(k));
            }
        }

        temp.generate(v, depth + 1);
        children.push_back(temp);        
    }
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

    program *crossover = result.copy(&a, p1[a1]);
    crossover->copy(p2[b1], NULL);

    // now work out unqie variables -- search instructions, using unordered_mAP
    // for result "start" of program, to copy over variables

    return result;
}

std::vector<polymorphic::program*> polymorphic::program::deconstruct(polymorphic::program &a)
{
    std::stack<program*> stack;
    std::vector<program*> all;

    stack.push(&a);

    while(!stack.empty())
    {
        program *t = stack.top();
        stack.pop();

        all.push_back(t);

        for(int i = 0; i < t->children.size(); ++i)
        {            
            stack.push(&a.children[i]);
        }
    }

    return all;
}

polymorphic::program *polymorphic::program::copy(program *source, program *until)
{
    if(source != until)
    {
        block = source->block;
        variables = source->variables;
        instructions = source->instructions;
        for(int i = 0; i < source->children.size(); ++i)
        {
            program p;
            p.copy(&source->children[i], until);
            children.push_back(p);
        }
    }
    else return this;

    return NULL;
}

std::string polymorphic::program::get(int depth)
{    
	auto tabs = [](int depth) 
	{ 
		std::string result;

        for(int i = 0; i < depth; ++i)
        {
            result += "\t";
        }

        return result;
	};

    std::string result;

    result += block.declare(variables) + "{\n";
    result += variables.declare();
    result += instructions.declare(variables);
    
    for(int i = 0; i < children.size(); ++i)
    {
        program b = children[i];
        result += tabs(depth + 1) + b.get(depth + 1);
    }

    result += tabs(depth) + "}\n";

    return result;
}