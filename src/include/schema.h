#include "program.h"
#include "settings.h"
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

        program data;

        float _score;

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
        
        float score() { return _score; }

        void generate();

    public:
        std::string output() { return data.output(); }

    public:        
        schema cross(schema &value);
        void mutate();

    public:
        std::string run();        

    protected:
        float compare(std::string left, std::string right);
    };
};

#endif