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

// Sorting Test
TEST(AlgorithmTests, SortingTest) {
    std::vector<int> numbers = {4, 2, 7, 1, 9};
    std::sort(numbers.begin(), numbers.end());
    auto rhs = std::vector<int>{1, 2, 4, 7, 9};
    ASSERT_EQ(numbers, rhs);
}

// Searching Test
TEST(AlgorithmTests, SearchingTest) {
    std::vector<int> numbers = {1, 2, 4, 7, 9};
    auto it = std::find(numbers.begin(), numbers.end(), 4);
    ASSERT_NE(it, numbers.end());
    ASSERT_EQ(*it, 4);
}

// Transform Test
TEST(AlgorithmTests, TransformTest) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), [](int n) { return n * 2; });
    auto rhs = std::vector<int>{2, 4, 6, 8, 10};
    ASSERT_EQ(numbers, rhs);
}

// Accumulation Test
TEST(AlgorithmTests, AccumulationTest) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    ASSERT_EQ(sum, 15);
}

// Unique Test
TEST(AlgorithmTests, UniqueTest) {
    std::vector<int> numbers = {1, 2, 2, 3, 4, 4, 4, 5};
    auto newEnd = std::unique(numbers.begin(), numbers.end());
    numbers.erase(newEnd, numbers.end());
    auto rhs = std::vector<int>{1, 2, 3, 4, 5};
    ASSERT_EQ(numbers, rhs);
}

// Additional Test: Reverse Test
TEST(AlgorithmTests, ReverseTest) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::reverse(numbers.begin(), numbers.end());
    auto rhs = std::vector<int>{5, 4, 3, 2, 1};
    ASSERT_EQ(numbers, rhs);
}

// Additional Test: Fill Test
TEST(AlgorithmTests, FillTest) {
    std::vector<int> numbers(5);
    std::fill(numbers.begin(), numbers.end(), 42);
    auto rhs = std::vector<int>{42, 42, 42, 42, 42};
    ASSERT_EQ(numbers, rhs);
}

// Additional Test: Count Test
TEST(AlgorithmTests, CountTest) {
    std::vector<int> numbers = {1, 2, 2, 3, 4, 4, 4, 5};
    int count = std::count(numbers.begin(), numbers.end(), 4);
    ASSERT_EQ(count, 3);
}

// Add more tests as needed

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}