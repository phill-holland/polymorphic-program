#include "population.h"
#include <iostream>
#include <string.h>

using namespace std;

void run()
{
    polymorphic::population p(100);
    p.go();

    polymorphic::schema best = p.best();
    
    std::cout << "Score " << best.score() << "\r\n";
    std::cout << best.output();
}

int main(int argc, char *argv[])
{  
    polymorphic::population p(1);

    polymorphic::program a,b;

    a.generate();
    b.generate();

    polymorphic::program c = polymorphic::program::cross(a,b);
            
    cout << a.output() << "\r\n";

    std::string output = a.run();
    cout << output << "\r\n";
    //p.generate();
    //cout << p.output();
    
    return 0;
}