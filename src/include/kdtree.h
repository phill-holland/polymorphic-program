#include "kdpoint.h"
#include <vector>

#ifndef _DOMINANCE_KDTREE_KDTREE
#define _DOMINANCE_KDTREE_KDTREE

namespace dominance
{
    namespace kdtree
    {
        class kdtree
        {
            kdpoint **values;    
            kdpoint *root;

            std::vector<kdpoint*> unallocated;

            long dimensions;
            long length;
            bool init;

        public:
            kdtree(long dimensions, long length) { makeNull(); reset(dimensions, length); }
            ~kdtree() { cleanup(); }

            bool initalised() { return init; }
            void reset(long dimensions, long length);

            void insert(kdpoint *point);
            
            bool inside(const kdpoint &value, kdpoint *min, kdpoint *max);

            void remove(kdpoint &point, bool debug = false);
            bool exists(kdpoint &point);
            
        protected:
            bool isintersect(kdpoint *root, kdpoint *min, kdpoint *max);

        protected:
            kdpoint *min(kdpoint *x, kdpoint *y, kdpoint *z, int dimension);            
            kdpoint *min(kdpoint *T, int dim, unsigned long cd, bool debug);            
            kdpoint *remove(kdpoint &x, kdpoint *T,  int cd, bool debug);

        protected:
            kdpoint *pop();
            void push(kdpoint *source);

        protected:
            void makeNull();
            void cleanup();
        };
    };
};

#endif