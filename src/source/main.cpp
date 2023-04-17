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

    polymorphic::population p(settings, 200);//500); //200, was 300, try 400

    p.generate();
    p.go(400); // 600

    polymorphic::schema best = p.top();
    
    std::cout << best.output();
    std::tuple<std::string, bool, int, int> result = best.run();
    std::cout << std::get<0>(result);
}

int main(int argc, char *argv[])
{  
    run();
    
    return 0;
}