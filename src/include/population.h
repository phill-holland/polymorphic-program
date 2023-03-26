#include "templates/grammar.h"
#include "schema.h"
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
        population(templates::grammar *g, int size) { makeNull(); reset(g, size); }
        ~population() { cleanup(); }

        bool initalised() { return init; }
        void reset(templates::grammar *g, int size);

        void start();

    protected:
        void generate();
        bool iterate();

    protected:
        schema *tournament(int j);

    protected:
        void makeNull() { data = NULL; }
        void cleanup();
    };
};

#endif