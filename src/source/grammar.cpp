#include "grammar.h"

polymorphic::grammar::grammar()
{
    data.push_back("{");
    data.push_back("}");
    data.push_back("\"");
    data.push_back("(");
    data.push_back(")");
    data.push_back("[");
    data.push_back("]");
    data.push_back("<");
    data.push_back(">");
    data.push_back("if");
    data.push_back("else");
    data.push_back("=");
    data.push_back("==");
    data.push_back(";");
    data.push_back("-");
    data.push_back("+");
    data.push_back("*");
    data.push_back("/");
    data.push_back("#");
    data.push_back(":");
    data.push_back(":");
    data.push_back("for");
    data.push_back("return");
    data.push_back("int");    
    data.push_back("void");
    data.push_back("\n");

    for(int i = 0; i < 10; ++i)
    {
        data.push_back(std::to_string(i));
    }

    for(char i = 'a'; i <= 'z'; ++i)
    {
        std::string temp;
        temp += i;
        data.push_back(temp);
    }
}

std::string polymorphic::grammar::get(int index)
{
    std::string result;

    if((index < 0)||(index >= data.size())) return result;

    return data[index];

    return result;
}

int polymorphic::grammar::length()
{
    return data.size();
}