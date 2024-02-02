/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <gtest/gtest.h>

namespace
{
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

    // Test: Compile-Time Factorial
    template <int N>
    struct Factorial
    {
        static constexpr int value = N * Factorial<N - 1>::value;
    };

    template <>
    struct Factorial<0>
    {
        static constexpr int value = 1;
    };

    TEST(TemplateAdvanced, CompileTimeFactorial)
    {
        constexpr int result = Factorial<5>::value;
        EXPECT_EQ(result, 120);
    }

// Test: Type Erasure with std::function
#include <functional>

    template <typename T>
    class TypeErasedFunction
    {
    public:
        template <typename U>
        TypeErasedFunction(U func) : function_(func) {}

        T operator()(T value) const
        {
            return function_(value);
        }

    private:
        std::function<T(T)> function_;
    };

    TEST(TemplateAdvanced, TypeErasureWithFunction)
    {
        TypeErasedFunction<int> square([](int x)
                                       { return x * x; });
        EXPECT_EQ(square(5), 25);
    }

    // Pair Concatenation
    template <typename T1, typename T2>
    auto pair_concat(const T1 &pair1, const T2 &pair2)
        -> std::pair<typename T1::first_type, typename T2::second_type>
    {
        return {pair1.first, pair2.second};
    }

    // Test
    TEST(TemplateAdvanced, PairConcatenation)
    {
        std::pair<int, double> pair1(42, 3.14);
        std::pair<std::string, char> pair2("Hello", '!');

        auto result = pair_concat(pair1, pair2);

        EXPECT_EQ(result, std::make_pair(42, '!'));
    }
}

// Add more tests as needed

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
