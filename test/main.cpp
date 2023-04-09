#include <gtest/gtest.h>

TEST(BasicProgramExectution, BasicAssertions)
{
    EXPECT_TRUE(true == true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
