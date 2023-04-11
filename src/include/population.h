#include "schema.h"
#include "settings.h"
#include <random>

#ifndef _POLYMORPHIC_POPULATION
#define _POLYMORPHIC_POPULATION

namespace polymorphic
{
    class population
    {
        static std::mt19937_64 generator;

        schema **data;
        int size;

        bool init;

    public:
        population(settings::settings config, int size) { makeNull(); reset(config, size); }
        ~population() { cleanup(); }

        bool initalised() { return init; }
        void reset(settings::settings config, int size);

        void generate();
        bool go(int iterations = 0);

        schema best();
        
    public:
        std::string output();

    protected:
        schema *tournament(int j);

    protected:
        void makeNull() { data = NULL; }
        void cleanup();
    };
};

#endif