#include <gtest/gtest.h>
#include <string>
#include "variables.h"
#include "instructions.h"
#include "program.h"

TEST(BasicProgramExecutionWithStringOutput, BasicAssertions)
{
    polymorphic::program p;

    polymorphic::vars::variable v;
    
    v.id = 1;
    v.type = 0;

    p.variables.values.push_back(v);

    std::string expected("hello world!");

    polymorphic::instrs::instruction i1;

    i1.type = 1;
    i1.variables.push_back(v);
    i1.parameters.push_back(expected);

    polymorphic::instrs::instruction i2;

    i2.type = 2;
    i2.variables.push_back(v);

    p.instructions.values.push_back(i1);
    p.instructions.values.push_back(i2);

    std::tuple<std::string, bool, int, int> result = p.run();

    EXPECT_TRUE(expected == std::get<0>(result));
}

TEST(BasicProgramExecutionAssignmentWithStringOutput, BasicAssertions)
{
    polymorphic::program p;

    polymorphic::vars::variable v1, v2;
    
    v1.id = 1;
    v1.type = 0;

    p.variables.values.push_back(v1);

    std::string expected("hello world!");

    polymorphic::instrs::instruction i1;

    i1.type = 1;
    i1.variables.push_back(v1);
    i1.parameters.push_back(expected);


    polymorphic::instrs::instruction i2;

    v2.id = 2;
    v2.type = 0;

    i2.type = 0;
    i2.variables.push_back(v2);
    i2.variables.push_back(v1);

    polymorphic::instrs::instruction i3;

    i3.type = 2;
    i3.variables.push_back(v2);

    p.instructions.values.push_back(i1);
    p.instructions.values.push_back(i2);
    p.instructions.values.push_back(i3);

    std::tuple<std::string, bool, int, int> result = p.run();

    EXPECT_TRUE(expected == std::get<0>(result));
}


TEST(BasicProgramExecutionIfStatementWithStringOutput, BasicAssertions)
{
    polymorphic::program main;

    polymorphic::vars::variable v1, v2, v3;
    
    v1.id = 1;
    v1.type = 0;

    main.variables.values.push_back(v1);

    std::string expected("hello world!");

    polymorphic::instrs::instruction i1;

    i1.type = 1;
    i1.variables.push_back(v1);
    i1.parameters.push_back(expected);

    main.instructions.values.push_back(i1);

    // ***

    v2.id = 2;
    v2.type = 1;

    main.variables.values.push_back(v2);

    v3.id = 3;
    v3.type = 1;

    main.variables.values.push_back(v3);

    polymorphic::instrs::instruction i2;

    i2.type = 1;
    i2.variables.push_back(v2);
    i2.parameters.push_back(std::string("5"));

    main.instructions.values.push_back(i2);

    polymorphic::instrs::instruction i3;

    i3.type = 1;
    i3.variables.push_back(v3);
    i3.parameters.push_back(std::string("6"));

    main.instructions.values.push_back(i3);

    polymorphic::program _if;

    _if.block.type = 0;
    _if.block.parameters.push_back(std::string("<"));

    _if.block.variables.push_back(v2);
    _if.block.variables.push_back(v3);

    polymorphic::instrs::instruction i4;

    i4.type = 2;
    i4.variables.push_back(v1);

    _if.instructions.values.push_back(i4);

    main.children.push_back(_if);

    std::tuple<std::string, bool, int, int> result = main.run();

    EXPECT_TRUE(expected == std::get<0>(result));
}

TEST(BasicProgramExecutionForLoopWithStringOutput, BasicAssertions)
{
    polymorphic::program main;

    polymorphic::vars::variable v1, v2;
    
    v1.id = 1;
    v1.type = 0;

    main.variables.values.push_back(v1);

    std::string expected("ha!ha!ha!ha!ha!ha!ha!ha!ha!");

    polymorphic::instrs::instruction i1;

    i1.type = 1;
    i1.variables.push_back(v1);
    i1.parameters.push_back("ha!");

    main.instructions.values.push_back(i1);

    // ***

    v2.id = 2;
    v2.type = 1;

    main.variables.values.push_back(v2);

    polymorphic::program _for;

    _for.block.type = 1;
    _for.block.parameters.push_back(std::string("10"));

    _for.block.variables.push_back(v2);

    polymorphic::instrs::instruction i4;

    i4.type = 2;
    i4.variables.push_back(v1);

    _for.instructions.values.push_back(i4);

    main.children.push_back(_for);

    std::tuple<std::string, bool, int, int> result = main.run();

    EXPECT_TRUE(expected == std::get<0>(result));
}

TEST(BasicProgramExecutionForLoopWithIfAndStringOutput, BasicAssertions)
{
    polymorphic::program main;

    polymorphic::vars::variable v1, v2, v4;
    
    v1.id = 1;
    v1.type = 0;

    main.variables.values.push_back(v1);

    v4.id = 4;
    v4.type = 1;

    main.variables.values.push_back(v4);

    std::string expected("ha!ha!ha!ha!ha!");

    polymorphic::instrs::instruction i1;

    i1.type = 1;
    i1.variables.push_back(v1);
    i1.parameters.push_back("ha!");

    main.instructions.values.push_back(i1);

    polymorphic::instrs::instruction i2;

    i2.type = 1;
    i2.variables.push_back(v4);
    i2.parameters.push_back("5");

    main.instructions.values.push_back(i2);

    v2.id = 2;
    v2.type = 1;

    main.variables.values.push_back(v2);

    polymorphic::program _for;

    _for.block.type = 1;
    _for.block.parameters.push_back(std::string("10"));

    _for.block.variables.push_back(v2);

    polymorphic::program _if;
    
    _if.block.type = 0;
    _if.block.parameters.push_back(std::string(">="));

    _if.block.variables.push_back(v2);
    _if.block.variables.push_back(v4);

    polymorphic::instrs::instruction i4;

    i4.type = 2;
    i4.variables.push_back(v1);

    _if.instructions.values.push_back(i4);

    _for.children.push_back(_if);

    main.children.push_back(_for);

    std::tuple<std::string, bool, int, int> result = main.run();

    EXPECT_TRUE(expected == std::get<0>(result));
}

TEST(BasicProgramBasicCross, BasicAssertions)
{
    std::string expected = R"(#include <iostream>
using namespace std;
 int main() {{
string b = "";
int c = 0;
int d = 0;
if (d>=c){
cout << b;
}
}
return 0;
})";

    polymorphic::program main;

    polymorphic::vars::variable v1, v2, v4;
    
    v1 = main.variables.get(0);
    v4 = main.variables.get(1);

    polymorphic::instrs::instruction i1;

    i1.type = 1;
    i1.variables.push_back(v1);
    i1.parameters.push_back("ha!");

    main.instructions.values.push_back(i1);

    polymorphic::instrs::instruction i2;

    i2.type = 1;
    i2.variables.push_back(v4);
    i2.parameters.push_back("5");

    main.instructions.values.push_back(i2);

    v2 = main.variables.get(1);

    polymorphic::program _for;

    _for.block.type = 1;
    _for.block.parameters.push_back(std::string("10"));

    _for.block.variables.push_back(v2);

    polymorphic::program _if;
    
    _if.block.type = 0;
    _if.block.parameters.push_back(std::string(">="));

    _if.block.variables.push_back(v2);
    _if.block.variables.push_back(v4);

    polymorphic::instrs::instruction i4;

    i4.type = 2;
    i4.variables.push_back(v1);

    _if.instructions.values.push_back(i4);

    _for.children.push_back(_if);

    main.children.push_back(_for);

    polymorphic::program output = polymorphic::program::cross(main, main, 1, 2);

    std::string result = output.output();
    
    expected.erase(std::remove(expected.begin(), expected.end(), '\n'), expected.cend());
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.cend());

    EXPECT_TRUE(expected == result);
}

TEST(BasicProgramBasicCrossAndRemoveUnusedVariables, BasicAssertions)
{
    std::string expected = R"(#include <iostream>
using namespace std;
 int main() {{
string b = "";
int c = 0;
int d = 0;
if (d>=c){
cout << b;
}
}
return 0;
})";

    polymorphic::program main;

    polymorphic::vars::variable v1, v2, v4;
    
    v1 = main.variables.get(0);
    v4 = main.variables.get(1);

    polymorphic::vars::variable throw_away = main.variables.get(2);

    polymorphic::instrs::instruction i1;

    i1.type = 1;
    i1.variables.push_back(v1);
    i1.parameters.push_back("ha!");

    main.instructions.values.push_back(i1);

    polymorphic::instrs::instruction i2;

    i2.type = 1;
    i2.variables.push_back(v4);
    i2.parameters.push_back("5");

    main.instructions.values.push_back(i2);

    v2 = main.variables.get(1);

    polymorphic::program _for;

    _for.block.type = 1;
    _for.block.parameters.push_back(std::string("10"));

    _for.block.variables.push_back(v2);

    polymorphic::program _if;
    
    _if.block.type = 0;
    _if.block.parameters.push_back(std::string(">="));

    _if.block.variables.push_back(v2);
    _if.block.variables.push_back(v4);

    polymorphic::instrs::instruction i4;

    i4.type = 2;
    i4.variables.push_back(v1);

    _if.instructions.values.push_back(i4);

    _for.children.push_back(_if);

    main.children.push_back(_for);

    polymorphic::program output = polymorphic::program::cross(main, main, 1, 2);    
    output = output.unused();

    std::string result = output.output();

    expected.erase(std::remove(expected.begin(), expected.end(), '\n'), expected.cend());
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.cend());

    EXPECT_TRUE(expected == result);
}

TEST(BasicProgramBasicMutation, BasicAssertions)
{
    std::string expected = R"(#include <iostream>
using namespace std;
 int main() {{
string b = "";
int c = 0;
bool d = false;
int e = 0;
b="ha!";
c=5;
for (e;e<10;++e){
if (e>=c){
cout << b;
}
}
}
return 0;
})";

    polymorphic::program main;

    polymorphic::vars::variable v1, v2, v4;
    
    v1 = main.variables.get(0);
    v4 = main.variables.get(1);

    polymorphic::vars::variable throw_away = main.variables.get(2);

    polymorphic::instrs::instruction i1;

    i1.type = 1;
    i1.variables.push_back(v1);
    i1.parameters.push_back("ha!");

    main.instructions.values.push_back(i1);

    polymorphic::instrs::instruction i2;

    i2.type = 1;
    i2.variables.push_back(v4);
    i2.parameters.push_back("5");

    main.instructions.values.push_back(i2);

    v2 = main.variables.get(1);

    polymorphic::program _for;

    _for.block.type = 1;
    _for.block.parameters.push_back(std::string("10"));

    _for.block.variables.push_back(v2);

    polymorphic::program _if;
    
    _if.block.type = 0;
    _if.block.parameters.push_back(std::string(">="));

    _if.block.variables.push_back(v2);
    _if.block.variables.push_back(v4);

    polymorphic::instrs::instruction i4;

    i4.type = 2;
    i4.variables.push_back(v1);

    _if.instructions.values.push_back(i4);

    _for.children.push_back(_if);

    main.children.push_back(_for);

    main.mutate();

    std::string result = main.output();

    expected.erase(std::remove(expected.begin(), expected.end(), '\n'), expected.cend());
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.cend());

    EXPECT_TRUE(expected != result);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
