#include "variables.h"
#include "instructions.h"
#include "blocks.h"
#include "state.h"
#include "settings.h"
#include <string>
#include <random>
#include <vector>
#include <unordered_map>
#include <tuple>

#ifndef _POLYMORPHIC_PROGRAM
#define _POLYMORPHIC_PROGRAM

namespace polymorphic
{    
    class program
    {
        const static int OVERRUN = 100;//500;

        static std::mt19937_64 generator;

    public:
        blocks::block block;
        vars::variables variables;
        instrs::instructions instructions;

        std::vector<program> children;
        settings::settings configuration;

    public:
        program() { }

        program(settings::settings _configuration) 
        {
            configuration = _configuration;

            variables = vars::variables(configuration._variables.min, configuration._variables.max); 
            instructions = instrs::instructions(configuration._instructions.min, configuration._instructions.max);
        }

    public:
        void clear();
        void generate();  
        void mutate();
        //void mutant(polymorphic::program *source);
        
        std::tuple<std::string, bool, int, int> run();
        
        polymorphic::program unused();
        
        std::string output();

    public:
        static program cross(program &a, program &b, int c1 = -1, int c2 = -1);
        static std::vector<program*> deconstruct(program &a);        

    protected:
        std::string run(state &s, bool &overrun, int depth, int &max_depth, int &instr_counter);

    protected:
        void copy(program *source, program *until, program *end,
                  polymorphic::program *alt_source, 
                  std::unordered_map<int, std::tuple<vars::variable,int>> &result);
        void copy(program *source,  polymorphic::program *end, std::unordered_map<int, std::tuple<vars::variable,int>> &result);
        
        void unique(std::unordered_map<int, std::tuple<vars::variable,int>> &result, vars::variables &input, bool ignore_assignments = false);
        
    protected: 
        std::string get(int depth);
        void generate(vars::variables &v, int depth);
    };
};

#endif