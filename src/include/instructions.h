#include "variables.h"
#include <string>
#include <random>
#include <vector>

#ifndef _POLYMORPHIC_INSTRUCTIONS
#define _POLYMORPHIC_INSTRUCTIONS

namespace polymorphic
{
    namespace instrs
    {
        class instruction
        {
        public:            
            int type;

            std::vector<vars::variable> variables;
            std::vector<std::string> parameters;
        };
      
       class instructions
        {            
            static std::mt19937_64 generator;
        
            int min, max;

            std::vector<instruction> values;
            
        public:
            instructions(int _min = 0, int _max = 10) 
            { 
                min = _min; max = _max;
                
                clear();                 
            }
            ~instructions() { }

            void clear()
            {
                values.clear();
            }

            int isempty() { return values.size() == 0; }
            
            void generate(vars::variables &variables);
            std::string declare(vars::variables &variables);
        };
    
    };
};

#endif