/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <algorithm>
#include <vector>
#include <numeric>
#include <gtest/gtest.h>

// Google Test example for std::find_if
TEST(AlgorithmTests, FindIfEvenTest)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Test if find_if can find the first even number
    auto result = std::find_if(numbers.begin(), numbers.end(), [](int n)
                               { return n % 2 == 0; });
    ASSERT_NE(result, numbers.end());
    EXPECT_EQ(*result, 2);
}

// Google Test example for std::sort
TEST(AlgorithmTests, SortTest)
{
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 10, 6};

    // Test if sort can arrange numbers in ascending order
    std::sort(numbers.begin(), numbers.end());
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(numbers, expected);
}

// Google Test example for std::accumulate
TEST(AlgorithmTests, AccumulateTest)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Test if accumulate can sum the numbers
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    EXPECT_EQ(sum, 15);
}

// Add more tests as needed

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    std::cout << "Hello world!" << std::endl;

    return RUN_ALL_TESTS();
}