#include "variables.h"
#include "state.h"
#include "settings.h"
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
            static std::mt19937_64 generator;

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
            bool evaulate(state &s);
            
            bool _if(state &s);
            bool _loop(state &s);

            void mutate(settings::settings configuration, vars::variables &vars);

        public:
            void copy(block &source, std::unordered_map<int, std::tuple<vars::variable,int>> map);
        };
    };
};

#endif