/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

// Function to square an integer
int square(int x)
{
    return x * x;
}

// Function to double an integer
int doubleValue(int x)
{
    return 2 * x;
}

// Function to apply a given operation to each element in a vector
void applyOperation(const std::vector<int> &input, int (*operation)(int))
{
    for (int value : input)
    {
        std::cout << operation(value) << " ";
    }
    std::cout << std::endl;
}

// Test case for using function pointers with algorithms
TEST(FunctionPointerTest, FunctionPointersWithAlgorithms)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Using std::transform with a function pointer to square each element
    std::vector<int> squaredNumbers;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(squaredNumbers), square);

    // Checking the squared numbers
    EXPECT_EQ(squaredNumbers, std::vector<int>({1, 4, 9, 16, 25}));
}

// Test case for passing function pointers as parameters
TEST(FunctionPointerTest, PassFunctionPointerAsParameter)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Applying the square function using a function pointer
    testing::internal::CaptureStdout(); // Redirect cout to a buffer for comparison
    applyOperation(numbers, square);
    std::string outputSquare = testing::internal::GetCapturedStdout();
    EXPECT_EQ(outputSquare, "1 4 9 16 25 \n"); // Check against expected output

    // Applying the doubleValue function using a function pointer
    testing::internal::CaptureStdout(); // Redirect cout to a buffer for comparison
    applyOperation(numbers, doubleValue);
    std::string outputDouble = testing::internal::GetCapturedStdout();
    EXPECT_EQ(outputDouble, "2 4 6 8 10 \n"); // Check against expected output
}

// Test case for using function pointers in a callback context
TEST(FunctionPointerTest, FunctionPointersInCallback)
{
    int result = 0;

    // Callback function that squares the given number
    // Can use 'auto' instead of std::function
    std::function<void(int)> callback = [&result](int x)
    {
        result = square(x);
    };

    // Calling the callback function
    callback(5);

    // Checking the result
    EXPECT_EQ(result, 25);
}

// Callback function that applies a custom operation to each element in a vector
// The syntax <ReturnType(Parameters)> describes the function type
void applyCallback(const std::vector<int> &input, std::function<int(int)> callback)
{
    for (const auto &value : input)
    {
        std::cout << callback(value) << " ";
    }
    std::cout << std::endl;
}

// Custom callback function using a lambda with captured variable
int multiplyWithFactor(int x, int factor)
{
    return x * factor;
}

// Test case for using a custom callback function with lambda and captured variable
TEST(CallbackTest, CustomCallbackWithLambda)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    int factor = 3;

    // Using a lambda as a custom callback with a captured variable
    auto customCallback = [&factor](int x)
    {
        return multiplyWithFactor(x, factor);
    };

    // Applying the custom callback
    applyCallback(numbers, customCallback);
    // Output: 3 6 9 12 15
}

// Custom callback function using a function object
template <typename T>
struct PowerFunction
{
    T exponent;

    PowerFunction(T exp) : exponent(exp) {}

    T operator()(T x) const
    {
        return std::pow(x, exponent);
    }
};

// Test case for using a custom callback function with a function object
TEST(CallbackTest, CustomCallbackWithFunctionObject)
{
    std::vector<int> numbers = {2, 3, 4};
    int exponent = 3;

    // Creating a function object with a custom callback
    PowerFunction<int> powerCallback(exponent);

    // Applying the custom callback using a function object
    applyCallback(numbers, powerCallback);
    // Output: 8 27 64

    PowerFunction<double> powerFunction{3.0};

    // Call the object as if it were a function
    double result = powerFunction(2.0);
    EXPECT_EQ(result, 8);
}

// Custom callback function using a free-standing function
int addTwo(int x)
{
    return x + 2;
}

// Test case for using a custom callback function with a free-standing function
TEST(CallbackTest, CustomCallbackWithFreeStandingFunction)
{
    std::vector<int> numbers = {5, 8, 11};

    // Applying a custom callback using a free-standing function
    applyCallback(numbers, addTwo);
    // Output: 7 10 13
}

// Main function for running the tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
