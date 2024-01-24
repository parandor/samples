/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include "add_values.h"
#include <gtest/gtest.h>

TEST(AddValuesTest, EmptyVector)
{
    std::vector<int> emptyVector;
    EXPECT_EQ(addValues(emptyVector), 0) << "Adding an empty vector should result in 0.";
}

TEST(AddValuesTest, Integers)
{
    std::vector<int> integers = {1, 2, 3, 4, 5};
    EXPECT_EQ(addValues(integers), 15) << "Sum of integers should be 15.";
}

TEST(AddValuesTest, Doubles)
{
    std::vector<double> doubles = {1.1, 2.2, 3.3, 4.4};
    EXPECT_DOUBLE_EQ(addValues(doubles), 11.0) << "Sum of doubles should be 11.0.";
}

TEST(AddValuesTest, Overflow)
{
    std::vector<int> overflowValues = {std::numeric_limits<int>::max(), 1};
    EXPECT_THROW(addValues(overflowValues), std::overflow_error)
        << "Adding values causing overflow should throw an exception.";
}

TEST(AddValuesTest, Underflow)
{
    std::vector<int> underflowValues = {std::numeric_limits<int>::min(), -1};
    EXPECT_THROW(addValues(underflowValues), std::underflow_error)
        << "Adding values causing overflow should throw an exception.";
}

// Add more tests as needed

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}