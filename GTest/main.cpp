#include <gtest/gtest.h>

// Note this file doesn't have a main function as it is provided by the gtest_main library
// If you want you can add a main and call RUN_ALL_TESTS() yourself

// USE the TEST macro to define a test where the first argument is the test group
// and the second is the test name
TEST(IntEqual, equalTest)
{
    EXPECT_EQ(1, 1);
}

TEST(IntEqual, notEqualTest)
{
    EXPECT_NE(1, 2);
}

TEST(BoolTests, trueTest)
{
    EXPECT_TRUE(true);
}

TEST(BoolTests, falseTest)
{
    EXPECT_FALSE(false);
}

TEST(StringCompare, stringTest)
{
    EXPECT_STREQ("Hello", "Hello");
}

TEST(StringCompare, stringTest2)
{
    EXPECT_STRNE("Hello", "World");
}

// Floats must be tested differently, we can use EXPECT_FLOAT_EQ or EXPECT_DOUBLE_EQ
// This is because floating point numbers are not exact and can have rounding errors
// We can also use near for other more complex comparisons
TEST(FloatTests, floatTest)
{
    EXPECT_FLOAT_EQ(1.0f, 1.0f);
}

TEST(FloatTests, doubleTest)
{
    EXPECT_DOUBLE_EQ(1.0, 1.0);
}

TEST(FloatTests, nearTest)
{
    EXPECT_NEAR(1.0, 1.1, 0.2);
}
TEST(FloatTests, nearTestFloat)
{
    EXPECT_NEAR(1.0f, 1.1f, 0.2f);
}

TEST(Excptions, exceptionTest)
{
    EXPECT_THROW(throw std::runtime_error("message"), std::runtime_error);
}
