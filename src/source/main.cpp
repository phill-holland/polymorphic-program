#include "population.h"
#include "settings.h"
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

    polymorphic::settings::settings settings;

    settings._children.depth = 3;
    settings._children.max = 5;

    settings._instructions.min = 1;
    settings._instructions.max = 5;

    settings._loop.max = 5;

    polymorphic::program a(settings),b;

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