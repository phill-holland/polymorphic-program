#include "block.h"
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

        block data;

        float _score;

    public:
        schema() { reset(); }
        ~schema() { }

    public:
        void clear() { data.clear(); }
        void reset();
        
        float score() { return _score; }

        void generate();

    public:
        std::string output() { return data.output(); }

    public:        
        schema cross(schema &value);
        void mutate();

    public:
        void run();        
    };
};

#endif