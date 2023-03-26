#include "templates/grammar.h"
#include <string>
#include <random>
#include <vector>

#ifndef _POLYMORPHIC_SCHEMA
#define _POLYMORPHIC_SCHEMA

namespace polymorphic
{
    class schema
    {
        static std::mt19937_64 generator;

        templates::grammar *grammar;

        std::vector<int> data;

        float _score;
        int _min, _max;

    public:
        schema(templates::grammar *g, int min, int max) { reset(g, min, max); }
        ~schema() { }

    public:
        void clear() { data.clear(); }
        void reset(templates::grammar *g, int min, int max);
        
        float score() { return _score; }

        void generate();

    public:        
        schema cross(schema &value);
        void mutate();

    public:
        void run();        
    };
};

#endif