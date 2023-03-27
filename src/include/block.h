#include "templates/grammar.h"
#include <string>
#include <random>
#include <vector>

#ifndef _POLYMORPHIC_BLOCK
#define _POLYMORPHIC_BLOCK

namespace polymorphic
{
    class variable
    {
        static std::mt19937_64 generator;

    public:
        int type;
        std::string name;
    };

    class instruction
    {
    public:
        int type;
        std::string value;
    };
    
    class block
    {
        static std::mt19937_64 generator;

    public:
        int type;
        std::string value;

        std::vector<variable> variables;
        std::vector<instruction> instructions;
        std::vector<block> children;

    public:
        void generate();        
        std::string output();

    protected: 
        std::string get();
        void generate(std::vector<std::string> &names, std::vector<variable> &vars, int depth);
        variable pick(std::vector<variable> &vars, int type);
    };
};

#endif