#ifndef _POLYMORPHIC_SETTINGS
#define _POLYMORPHIC_SETTINGS

namespace polymorphic
{
    namespace settings
    {
        class children
        {
            static const int DEPTH = 5;
            static const int MAX = 10;

        public:
            int depth;
            int max;

        public:    
            children(int _depth = DEPTH, int _max = MAX) { depth = _depth; max = _max; }
        };

        class variables
        {
            static const int MIN = 1;
            static const int MAX = 5;

        public:
            int min, max;

        public:
            variables(int _min = MIN, int _max = MAX) { min = _min; max = _max; }
        };

        class instructions
        {
            static const int MIN = 0;
            static const int MAX = 10;

        public:
            int min, max;
            
        public:
            instructions(int _min = MIN, int _max = MAX) { min = _min; max = _max; }
        };

        class loop      
        {
            static const int MIN = 0;
            static const int MAX = 20;

        public:
            int min;
            int max;

        public:
            loop(int _min = MIN, int _max = MAX) { min = _min; max = _max; }
        };

        class settings
        {
        public:
            children _children;
            variables _variables;
            instructions _instructions;
            loop _loop;
        };
    };
};

#endif