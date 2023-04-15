#include "population.h"
#include "settings.h"
#include <iostream>
#include <string.h>

using namespace std;

void run()
{
    polymorphic::settings::settings settings;

    settings._children.depth = 3; // 3
    settings._children.max = 5; // 5

    settings._instructions.min = 1; //1
    settings._instructions.max = 15; //25 //15

    settings._loop.min = 1; // 1
    settings._loop.max = 5; // 5

    polymorphic::population p(settings, 100); //200

    p.generate();
    p.go(200); // 600

    polymorphic::schema best = p.best();
    
    //std::cout << "Score " << best.score() << "\r\n";
    std::cout << best.output();
    std::cout << best.run();
}

int main(int argc, char *argv[])
{  
    run();
    
    return 0;
}