#include <unordered_map>
#include <string>
#include "variables.h"

#ifndef _POLYMORPHIC_STATE
#define _POLYMORPHIC_STATE

namespace polymorphic
{
    class state
    {
    public:
        std::unordered_map<int, std::string> strings;
        std::unordered_map<int, int> integers;
        std::unordered_map<int, bool> booleans;
        
    public:
        state(vars::variables &v) { reset(v); }

        void reset(vars::variables &v);

        void clear()
        {
            strings.clear();
            integers.clear();
            booleans.clear();
        }
    };    
};

#endif