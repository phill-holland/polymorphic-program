#include "schema.h"

#ifndef _POLYMORPHIC_POPULATION
#define _POLYMORPHIC_POPULATION

namespace polymorphic
{
    class population
    {
        schema **data;

        bool init;

    public:
        population(int size) { }
        ~population() { }

        bool initalised() { return init; }
        void reset(int size) { }
    
    protected:
        void makeNull() { }
        void cleanup() { }
    };
};

#endif