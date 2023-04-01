#include "variables.h"
#include <string>
#include <random>
#include <vector>

#ifndef _POLYMORPHIC_BLOCKS
#define _POLYMORPHIC_BLOCKS

namespace polymorphic
{
    namespace blocks
    {
        class block
        {
        public:
            int type;

            std::vector<vars::variable> variables;
            std::vector<std::string> parameters;

        public:            
            block() 
            { 
                clear(); 
            }

            void clear()
            {
                type = 0;

                variables.clear();
                parameters.clear();
            }

            std::string declare(vars::variables &vars);
        };
    };
};

#endif