#include "program.h"
#include "settings.h"
#include "score.h"
#include <string>
#include <random>
#include <vector>
#include <tuple>

#ifndef _POLYMORPHIC_SCHEMA
#define _POLYMORPHIC_SCHEMA

namespace polymorphic
{
    class schema
    {
        static std::mt19937_64 generator;

        program data;

    public:
        score scores;

    public:
        schema() { reset(); }
        schema(polymorphic::settings::settings settings)
        {
            reset();
            data = program(settings);
        }

        ~schema() { }

    private:
        schema(program data)
        {
            reset();
            this->data = data;
        }

    public:
        void clear() { data.clear(); }
        void reset();
        
        void generate();

    public:
        std::string output() { return data.output(); }

    public:        
        schema cross(schema &value);
        void mutate();

    public:
        std::tuple<std::string, bool, int, int> run();           
    };
};

#endif