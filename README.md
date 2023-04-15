# Polymorphic Programming

This is a work in progress to demonstrate how to create computer programs which may have different code but still produces the same output.

In this example I attempt to generate as many different code variations that output "hello world", but it's application could be used for many different end results.

The basis for this code is using genetic algorithms, starting with a population of randomly generated programs and then testing each program for the fitness to a problem (i.e. running the code)

For example, the simplest way to produce "hello world" may be;

```
#include <iostream>

int main()
{
    std::cout << "hello world!";

    return 0;
}
```

However, you could also write;

```
#include <iostream>

int main()
{
    char[] data = { 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!' };

    for(int i = 0; i < 12; ++i)
    {
        std::cout << data[i];
    }

    return 0;
}

```

And even more indirectly;

```
#include <iostream>

int main()
{
    int z = 12;
    int y = 2;

    char[] data = { 'h' };
    
    for(int i = 0; i < 1; ++i )
    {
        std::cout << data[i];
    }
    
    if(z / 2 == 6)
    {
        std::cout <<  "ello ";   
    }

    y = 6;

    if(y < z)
    {
        std::cout << "world!";
    }

    return 0;
}
```

From an output point of view, all these programs are equally valid, however illogical the code producing the output may be! (however in these examples, we are ignoring any compiler optimisations that may negate seemingly useless code).


# Algorithm

- A large array (or a population), containing randomly generated programs is created (see below for details)

- Each program is run, and then scored based on how close it's output to "hello world" is (a number between 0.0f and 1.0f)

- Two programs are picked, that have outputted the closest string to "hello world" and then randomly combined with each other, to create a new program

- The new program is then added to the population, and then re-run and re-scored

- This process is repeated until a program with a score of 1.0f is reached

# Randomly Generating Snytax Correct Code

There are many different ways to generate random code, you could technically generate a random set of characters and using genetic algorithms eventually expect it to eventually produce a valid program (1 million monkeys on a million typewriters, expecting them to produce Shakespere isn't out of the realms of possibility with modern parallel hardware, such as GPUs) however this could a very long time to find a solution, so was rejected in favour of an alternative algorithm.

For that alternative, consider a program as a series of blocks, those blocks may represent a function, an control-block inside an IF statement, or a loop.  Each block may use a set of variables and have it's own set of instructions, such as assigning a value of a variable to another, initialising a variable to a value, or output a variable to the console window.  With these set of base rules, we can start to build an algorithm that will always generate syntax correct code, that will run and compile no matter ho random a mess it would seem from an initial glance.

For example, the creation of a new "block" of code may look like;

```
int x = rand(0,3);
block b;

if(x == 0)
{
    b = new block("if");
    b.init();
} 
else if(x == 1)
{
    b = new block("loop");
    b.init();
}

class block
{
    string _type;

public:
    block(string type) { _type = type; }
    
    void init()
    {
        auto variables = generate_variables();
        generate_instructions(variables);
    }
};
```

Using genetic algorithms in this way might be considered redundant now(?) with the recent progress in fields of machine learning -- there may be potential here to have a customized variation of ChatGPT that performed this task more efficiently, simply asking it to generate all the same variations of the code it could think of, but where's the fun in that?

# Todo

- Test code crossover function (OKISH)

- Fix CROSSOVER IS NULL bug (DONE)

- Include top level input parameters to limit growth size of programs (DONE)

- ***Need a find unused variable function for each program (and remove) THIS NEXT!! (get used variables, then remap)

- Unused variables part 2, remove variables and instructions that are assigned to, but never used

- Mutate blocks update, ideally move blocks around and delete some randomly

- Fix tabbed output (DON'T CARE ABOUT ANYMORE)

- Need to parse/run output code inline (rather than running an external compiler and running on the OS) (ADDED, NOT TESTED)

- Add string output score function to test outputs afer program run (copy from another project) (DONE)

- Edit random string generator to only use "hello world" characters as grammar (DONE)

- Add code mutation function (DONE)

- Suppress output of anything that's not a string (i.e. integers/booleans) (DONEISH)

- Add google tests (DONE)

- Ensure in block._loop function, doesn't go into infinite loop DONEISH

- Include the generation code, as part of the randomly generated code (self replicating, can it generate code that generates copies of itself)

- Variable STATE INIT - GENERATE RANDOM INIT VARIABLES

- BUG SUPPRESS VARIABLE COMPARISONS WITH SELF

- BUG SUPPRESS VARIABLE ASSIGNMENTS TO SELF

# Running

- Ensure project is open within the VSCode development container
- Hit F5

# Requirements

The VSCode development container plugin is installed;

https://code.visualstudio.com/docs/remote/containers

Docker must also be installed;

https://docs.docker.com/get-docker/

This application, however is configured with linux based containers, and will not work correctly on Windows without modification.
