#include "population.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{  
    polymorphic::population p(1);

    p.generate();
    cout << p.output();
    
    return 0;
}