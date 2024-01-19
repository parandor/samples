#include <iostream>
#include <vector>
#include <numeric>
#include <gtest/gtest.h>

// Base case for recursion
template <typename T>
T sum(T value)
{
    return value;
}

template <typename T, typename... Args>
T sum(T first, Args... args)
{
    return first + sum(args...);
}

// Tests
TEST(SumFunction, Integers)
{
    EXPECT_EQ(sum(1, 2, 3, 4, 5), 15);
}

TEST(SumFunction, Doubles)
{
    EXPECT_DOUBLE_EQ(sum(1.0, 2.5, 3.5), 7.0);
}

TEST(SumFunction, MixSignedAndUnsigned)
{
    EXPECT_EQ(sum(1, -2, 3u, 4), 6);
}

TEST(SumFunction, Strings)
{
    std::string result = sum(std::string("Hello, "), std::string("world!"));
    EXPECT_EQ(result, "Hello, world!");
}

TEST(Accumulate, Integers)
{
    std::vector<int> vec = {1, 2, 33333, 4, 5, 6};
    auto res = std::accumulate(vec.begin(), vec.end(), 0);
    EXPECT_EQ(res, 33351);
}

// Add more tests as needed

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    std::cout << "Hello world!" << std::endl;

    return RUN_ALL_TESTS();
}
