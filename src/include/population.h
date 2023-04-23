#include "schema.h"
#include "settings.h"
#include "kdtree.h"
#include <random>

#ifndef _POLYMORPHIC_POPULATION
#define _POLYMORPHIC_POPULATION

namespace polymorphic
{
    class population
    {
        static const int minimum = 100, maximum = 10000;
        static std::mt19937_64 generator;

        dominance::kdtree::kdtree *approximation;

        schema **data;
        int size;

        bool init;

    public:
        population(settings::settings config, int size) { makeNull(); reset(config, size); }
        ~population() { cleanup(); }

        bool initalised() { return init; }
        void reset(settings::settings config, int size);

        void generate();
        polymorphic::schema go(int iterations = 0);

        schema top();
        
    public:
        std::string output();

    protected:
        schema *best(int j);
        int worst();

    protected:
        bool set(int index, schema &source);

    protected:
        int getch();
        
    protected:
        void makeNull();
        void cleanup();
    };
};

#endif