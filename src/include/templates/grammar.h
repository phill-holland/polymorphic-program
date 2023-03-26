#include <string>

#ifndef _POLYMORPHIC_GRAMMAR
#define _POLYMORPHIC_GRAMMAR

namespace polymorphic
{
    namespace templates
    {
        class grammar
        {
        public:
            virtual std::string get(int index) = 0;
            virtual int length() = 0;
        };
    };
};

#endif