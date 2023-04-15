#include <array>
#include <string>

#ifndef _POLYMORPHIC_SCORE
#define _POLYMORPHIC_SCORE

namespace polymorphic
{
    class score
    {
    public:
        const static int length = 13;

    public:
        std::array<float, length> scores;

    public:
        score() { clear(); }

        void clear();
        void compute(std::string value);

        float sum();
    };
};

#endif