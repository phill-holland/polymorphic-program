#include "block.h"

std::mt19937_64 polymorphic::block::generator(std::random_device{}());

void polymorphic::block::generate()
{
    std::vector<std::string> names;
    for(char i = 'a'; i <= 'z'; ++i)
    {
        std::string temp;
        temp += i;
        names.push_back(temp);
    }

    int vars = (std::uniform_int_distribution<int>{0, 10})(generator);
    for(int i = 0; i < vars; ++i)
    {
        variable temp;
        temp.type = (std::uniform_int_distribution<int>{0, 2})(generator); 
        temp.name = names.back();
        names.pop_back();
 
        variables.push_back(temp);
    }

    generate(names,variables,0);
}

void polymorphic::block::generate(std::vector<std::string> &names, std::vector<variable> &vars, int depth)
{
    if(depth > 5) return;

    int instrs = (std::uniform_int_distribution<int>{0, 10})(generator);
    for(int i = 0; i < instrs; ++i)
    {
        instruction temp;
        temp.type = (std::uniform_int_distribution<int>{0, 2})(generator); 

        if(temp.type == 0) // assignment, one var to another
        {
            int j = (std::uniform_int_distribution<int>{0, vars.size() - 1})(generator);
            int t = vars[j].type;

            variable a = pick(vars, t);
            variable b = pick(vars, t);

            temp.value = a.name + "=" + b.name;
        }
        else if(temp.type == 1) // assignment, variable new random thing
        {
            int j = (std::uniform_int_distribution<int>{0, vars.size() - 1})(generator);
            variable a = vars[j];

            if(a.type == 0) // string
            {
                // random string
                std::string s;
                int k = (std::uniform_int_distribution<int>{0, 10})(generator);
                for(int i = 0; i < k; ++i)
                {
                    int y = (std::uniform_int_distribution<int>{97, 122})(generator);
                    s += (char)y;
                }

                temp.value = a.name + "=\"" + s + "\""; 
            }
            else if(a.type == 1) // int
            {
                int k = (std::uniform_int_distribution<int>{0, 100})(generator);
                temp.value = a.name + "=" + std::to_string(k);
            }
            else if(a.type == 2) // bool
            {
                int k = (std::uniform_int_distribution<int>{0, 1})(generator);
                temp.value = a.name + "=" + (k == 0 ? "true" : "false");
            }
        }
        else if(temp.type == 3) // cout variable
        {
            int j = (std::uniform_int_distribution<int>{0, vars.size() - 1})(generator);
            variable a = vars[j];

            temp.value = "cout << " + a.name;
        }
        else if(temp.type == 4)
        {
            int j = (std::uniform_int_distribution<int>{0, vars.size() - 1})(generator);
            int t = vars[j].type;

            variable a = pick(vars, t);
            variable b = pick(vars, t);
            variable c = pick(vars, t);

            temp.value = a.name + "=" + b.name + " " + c.name;
        }

        instructions.push_back(temp);
    }

// generate instructions
// set variables = new value
// set variable to another variable
// or maths
// +,-,/,* if int

    int length = (std::uniform_int_distribution<int>{0, 10})(generator);
    
    for(int i = 0; i < length; ++i)
    {
        block temp;
        temp.type = (std::uniform_int_distribution<int>{0, 1})(generator);

        if(temp.type == 0)
        {
            int j = (std::uniform_int_distribution<int>{0, vars.size() - 1})(generator);
            int t = vars[j].type;

            variable a = pick(vars, t);
            variable b = pick(vars, t);

            temp.value = "if (" + a.name;

            int k = (std::uniform_int_distribution<int>{0, 4})(generator);
            if(k == 0) temp.value += "<";
            else if(k == 1) temp.value += ">";
            else if(k == 2) temp.value += "<=";
            else if(k == 3) temp.value += ">=";
            else if(k == 4) temp.value += "==";

            temp.value += b.name + ")";
        }
        else if(temp.type == 1)
        {
            if(names.size() > 0)
            {
                std::string n = names.back();
                names.pop_back();

                int k = (std::uniform_int_distribution<int>{0, 20})(generator);

                temp.value = "for (int " + n + "=0;" + n + "<" + std::to_string(k) + ";++" + n + ")";
            }
        }

        temp.generate(names, vars, depth + 1);
        children.push_back(temp);        
    }
}

std::string polymorphic::block::output()
{
    std::string result;

    result = "#include <iostream>\nusing namespace std;\n int main() {";
    result += get();
    result += "return 0;\n}\n";
    
    return result;
}

std::string polymorphic::block::get()
{
    std::string result;

    result += value + "{\n";

    // string, int, bool
    for(int i = 0; i < variables.size(); ++i)
    {
        variable v = variables[i];
        if(v.type == 0) result += "string " + v.name + ";\n";
        else if(v.type == 1) result += "int " + v.name + ";\n";
        else if(v.type == 2) result += "bool " + v.name +";\n";
    }

    for(int i = 0; i <instructions.size(); ++i)
    {
        instruction in = instructions[i];
        result += in.value + ";\n";
    }

    for(int i = 0; i < children.size(); ++i)
    {
        block b = children[i];
        result += b.get();
    }

    result += "}\n";

    return result;
}

polymorphic::variable polymorphic::block::pick(std::vector<variable> &vars, int type)
{
    while(true) 
    {
        int i = (std::uniform_int_distribution<int>{0, vars.size() - 1})(generator);
        variable v = vars[i];

        if(v.type == type) return vars[i];
    };
}