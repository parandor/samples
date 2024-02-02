#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <execution>

/**
 * @file parallel_algorithms.cpp
 * @brief Testing parallel algorithms in C++ using Google Test.
 *
 * Parallel algorithms are a set of algorithms introduced in C++17 that leverage parallelism to perform
 * operations on data concurrently, potentially improving performance. These algorithms can operate on
 * multiple threads or use other parallel execution models depending on the implementation.
 *
 * Importance:
 * - Improved performance on multi-core systems.
 * - Efficient utilization of available resources for computation.
 * - Enhanced scalability for large datasets and computations.
 *
 * Use Cases:
 * - Parallel for_each: Apply a function to each element in parallel.
 * - Parallel transform: Apply a transformation to each element in parallel.
 * - Parallel reduce: Perform a binary operation on elements to produce a single result.
 * - Parallel transform_reduce: Combine transform and reduce operations in parallel.
 * - Parallel inclusive_scan: Compute inclusive prefix sums in parallel.
 *
 * Note: Parallelism effectiveness depends on the specific use case and the underlying hardware.
 */

namespace
{
    // Parallel for_each
    TEST(ParallelAlgorithmsTest, ParallelForEach)
    {
        std::vector<int> vec = {1, 2, 3, 4, 5};

        // Beginner level: Multiply each element by 2 in parallel
        std::for_each(std::execution::par, vec.begin(), vec.end(), [](int &num)
                      { num *= 2; });

        // Check the modified vector
        auto expected = std::vector<int>{2, 4, 6, 8, 10};
        ASSERT_EQ(vec, expected);
    }

    // Parallel transform
    TEST(ParallelAlgorithmsTest, ParallelTransform)
    {
        std::vector<int> vec = {1, 2, 3, 4, 5};
        std::vector<int> result(vec.size());

        // Intermediate level: Square each element in parallel
        std::transform(std::execution::par, vec.begin(), vec.end(), result.begin(), [](int num)
                       { return num * num; });

        // Check the result vector
        auto expected = std::vector<int>{1, 4, 9, 16, 25};
        ASSERT_EQ(result, expected);
    }

    // Parallel reduce
    TEST(ParallelAlgorithmsTest, ParallelReduce)
    {
        std::vector<int> vec = {1, 2, 3, 4, 5};

        // Beginner level: Calculate the sum of elements in parallel
        int sum = std::reduce(std::execution::par, vec.begin(), vec.end());

        // Check the sum
        ASSERT_EQ(sum, 15);
    }

    // Test fixture class template
    template <typename T>
    class TransformReduceTest : public ::testing::Test
    {
    protected:
        // Helper function to calculate the product of squares of odd numbers
        T calculateProductOfSquaresOfOdds(const std::vector<T> &vec)
        {
            return std::transform_reduce(
                vec.begin(), vec.end(),
                T(1),                 // Default value for the binary operation (identity element for multiplication)
                std::multiplies<T>(), // Binary operation (multiplication)
                // static cast to handle int, float, double
                [](T num)
                { return (static_cast<int>(num) % 2 == 1) ? num * num : T(1); } // Unary operation for odd numbers
            );
        }
    };

    // In Google Test, TYPED_TEST_SUITE and TYPED_TEST are macros used for creating typed test
    // fixtures and test cases that can be parameterized over multiple types. This allows you to
    // write test logic that can be reused for different types, enhancing code coverage and
    // promoting code reuse.

    // Define a typed test fixture
    typedef ::testing::Types<unsigned, short, int, float, double> MyTypes;
    TYPED_TEST_SUITE(TransformReduceTest, MyTypes);

    // Test case using typed test fixture
    TYPED_TEST(TransformReduceTest, ProductOfSquaresOfOdds)
    {
        std::vector<TypeParam> vec = {1, 2, 3, 4, 5};

        // Expected value calculation
        TypeParam expectedValue = 1 * 9 * 25;

        // Calculate the actual value
        TypeParam actualValue = this->calculateProductOfSquaresOfOdds(vec);

        // Check the result using ASSERT_EQ
        ASSERT_EQ(actualValue, expectedValue);
    }

    // Parallel inclusive_scan
    TEST(ParallelAlgorithmsTest, ParallelInclusiveScan)
    {
        std::vector<int> vec = {1, 2, 3, 4, 5};
        std::vector<int> result(vec.size());

        // Advanced level: Perform parallel inclusive scan
        std::inclusive_scan(std::execution::par, vec.begin(), vec.end(), result.begin());

        // Check the result vector
        auto expected = std::vector<int>{1, 3, 6, 10, 15};
        ASSERT_EQ(result, expected);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
