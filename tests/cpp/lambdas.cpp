/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <gtest/gtest.h>

// Lambda expression contruct:
//
// [capture](parameters) -> return_type {
//     // body of the lambda function
//     // ...
// }

namespace
{
    // Test case for capturing variables in lambda with mutable keyword
    TEST(LambdaTest, CaptureVariablesMutableTest)
    {
        int baseValue = 5;

        // Lambda capturing a variable by value with mutable keyword
        auto lambdaByValueMutable = [baseValue]() mutable
        {
            baseValue += 5; // Modifying the captured variable in a mutable lambda
            return baseValue * 2;
        };

        EXPECT_EQ(lambdaByValueMutable(), 20); // Captured by value, but modified within the lambda
        EXPECT_EQ(baseValue, 5);               // The original variable remains unchanged
    }

    // Test case for using lambda as a predicate in std::remove_if
    TEST(LambdaTest, LambdaAsPredicateTest)
    {
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        // Using std::remove_if with a lambda as a predicate to remove even numbers
        auto isEven = [](int value)
        {
            return value % 2 == 0;
        };
        numbers.erase(std::remove_if(numbers.begin(), numbers.end(), isEven), numbers.end());

        // Checking the remaining elements
        EXPECT_EQ(numbers, std::vector<int>({1, 3, 5, 7, 9}));
    }

    // Test case for using lambda with std::accumulate
    TEST(LambdaTest, LambdaWithAccumulateTest)
    {
        std::vector<int> numbers = {1, 2, 3, 4, 5};

        // Using std::accumulate with a lambda to calculate the product of elements
        auto product = std::accumulate(numbers.begin(), numbers.end(), 1, [](int acc, int value)
                                       { return acc * value; });

        // Checking the calculated product
        EXPECT_EQ(product, 120);
    }

    // Test case for a more complex lambda expression
    TEST(LambdaTest, ComplexLambdaExpressionTest)
    {
        // Using a lambda to create a function that calculates the nth Fibonacci number
        std::function<int(int)> fibonacci = [&fibonacci](int n) -> int
        {
            return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
        };

        // Testing the Fibonacci function
        EXPECT_EQ(fibonacci(0), 0);
        EXPECT_EQ(fibonacci(1), 1);
        EXPECT_EQ(fibonacci(2), 1);
        EXPECT_EQ(fibonacci(3), 2);
        EXPECT_EQ(fibonacci(4), 3);
        EXPECT_EQ(fibonacci(5), 5);
        EXPECT_EQ(fibonacci(6), 8);
    }

    // Additional test case for a simple lambda expression
    TEST(LambdaTest, SimpleLambdaExpressionTest)
    {
        // Using a lambda for a simple addition operation
        auto addFunction = [](int a, int b)
        {
            return a + b;
        };

        // Testing the lambda expression
        EXPECT_EQ(addFunction(2, 3), 5);
    }

    // Additional test case for a lambda expression with capture
    TEST(LambdaTest, LambdaWithCaptureTest)
    {
        int multiplier = 2;

        // Using a lambda with capture to create a multiplication function
        auto multiplyFunction = [multiplier](int x)
        {
            return x * multiplier;
        };

        // Testing the lambda expression
        EXPECT_EQ(multiplyFunction(4), 8);
    }

    // Additional test case for lambda as a predicate in std::remove_if
    TEST(LambdaTest, LambdaAsPredicateWithRemoveIfTest)
    {
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int threshold = 5;

        // Using lambda as a predicate to remove elements greater than the threshold
        auto isGreaterThanThreshold = [threshold](int value)
        {
            return value > threshold;
        };

        // Applying std::remove_if with the lambda predicate
        numbers.erase(std::remove_if(numbers.begin(), numbers.end(), isGreaterThanThreshold), numbers.end());

        // Checking the remaining elements
        EXPECT_EQ(numbers, std::vector<int>({1, 2, 3, 4, 5}));
    }

    // Additional test case for lambda as a predicate in std::find_if
    TEST(LambdaTest, LambdaAsPredicateWithFindIfTest)
    {
        std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};

        // Using lambda as a predicate to find the first word starting with 'b'
        auto startsWithB = [](const std::string &word)
        {
            return !word.empty() && word[0] == 'b';
        };

        // Applying std::find_if with the lambda predicate
        auto result = std::find_if(words.begin(), words.end(), startsWithB);

        // Checking the result
        EXPECT_EQ(*result, "banana");
    }

    // Additional test case for lambda as a predicate in std::sort
    TEST(LambdaTest, LambdaAsPredicateWithSortTest)
    {
        std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

        // Using lambda as a predicate to sort numbers in descending order
        std::sort(numbers.begin(), numbers.end(), [](int a, int b)
                  { return a > b; });

        // Checking the sorted elements
        EXPECT_EQ(numbers, std::vector<int>({9, 6, 5, 5, 5, 4, 3, 3, 2, 1, 1}));
    }
}

// Main function for running the tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
