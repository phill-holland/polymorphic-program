#include "variables.h"
#include "instructions.h"
#include "blocks.h"
#include <string>
#include <random>
#include <vector>

#ifndef _POLYMORPHIC_PROGRAM
#define _POLYMORPHIC_PROGRAM

namespace polymorphic
{    
    class program
    {
        static std::mt19937_64 generator;

    public:
        blocks::block block;
        vars::variables variables;
        instrs::instructions instructions;

        std::vector<program> children;

    public:
        program() { }

    public:
        void clear();
        void generate();        
        std::string output();

// need function, find used unique variables, return vector of vars::variables

    protected: 
        std::string get(int depth);
        void generate(vars::variables &v, int depth);
    };
};

#endif