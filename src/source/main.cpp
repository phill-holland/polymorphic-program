#include "population.h"
#include <iostream>
#include <string.h>

using namespace std;

// todo;
// 1) need a find unused variable function for each program (and remove)
// 2) fix tabbed output
// 3) need to parse/run output code inline 
// 4) edit random string generator to only use "hello world" characters as grammar.
// 5) test code crossover function
// 6) add code mutation function

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