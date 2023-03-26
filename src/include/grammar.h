#include "templates/grammar.h"
#include <vector>
#include <string>

#ifndef _POLYMORPHiC_TEMPLATES_GRAMMAR
#define _POLYMORPHIC_TEMPLATES_GRAMMAR

namespace polymorphic
{
    class grammar : public templates::grammar
    {
        std::vector<std::string> data;

    public:
        grammar();

    public:
        std::string get(int index);
        int length();
    };
};

#endif