#include <string>

#ifndef _POLYMORPHIC_SCHEMA
#define _POLYMORPHIC_SCHEMA

namespace polymorphic
{
    class schema
    {
        std::string data;

    public:
        schema() { }
        ~schema() { }

        void clear() { }

        void generate() { }
        schema cross(schema &a, schema &b) { return *this; }
    };
};

#endif