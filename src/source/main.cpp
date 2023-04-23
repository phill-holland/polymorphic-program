#include "population.h"
#include "settings.h"
#include <iostream>
#include <string.h>

using namespace std;

void run()
{
    polymorphic::settings::settings settings;

    settings._children.depth = 3;
    settings._children.max = 5;

    settings._instructions.min = 1;
    settings._instructions.max = 15; 

    settings._loop.min = 1;
    settings._loop.max = 5;

    polymorphic::population p(settings, 2000);

    p.generate();
    polymorphic::schema best = p.go(1000);

    std::cout << best.output();
    std::tuple<std::string, bool, int, int> result = best.run();
    std::cout << std::get<0>(result);
}

int main(int argc, char *argv[])
{  
    run();
    
    return 0;
}