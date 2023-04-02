#include "variables.h"
#include <string>
#include <random>
#include <vector>
#include <unordered_map>

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
            
        public:
            void copy(block &source, std::unordered_map<int, std::tuple<vars::variable,int>> map);
        };
    };
};

#endif