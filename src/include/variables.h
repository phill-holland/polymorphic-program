#include <string>
#include <random>
#include <vector>

#ifndef _POLYMORPHIC_VARIABLES
#define _POLYMORPHIC_VARIABLES

namespace polymorphic
{
    namespace vars
    {
        class variable
        {
        public:
            int id;
            int type;

        public:
            variable() { id = 0; type = 0; }
        };

        class variables
        {            
            static std::mt19937_64 generator;
        
            int min, max;
            int idx;

        public:
            std::vector<variable> values;
            
        public:
            variables(int _min = 1, int _max = 10) 
            { 
                min = _min; max = _max;
                
                clear();                 
            }
            ~variables() { }

            void clear();

            int isempty() { return values.size() == 0; }

            void generate();

            std::string name(variable &v);

            std::string declare();

        public:
            variable get();
            variable get(int type);

        public:
            variable pick();
            variable pick(int type);

        protected:
            int inc() { idx += 1; return idx; }
        };
    };
};

#endif