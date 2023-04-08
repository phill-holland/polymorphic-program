#include "population.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{  
    polymorphic::population p(1);

    polymorphic::program a,b;

    a.generate();
    b.generate();

    polymorphic::program c = polymorphic::program::cross(a,b);

    cout << c.output();

    //p.generate();
    //cout << p.output();
    
    return 0;
}