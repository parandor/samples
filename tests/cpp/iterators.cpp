#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

// Beginner test: Check if iterators can traverse a vector
TEST(IteratorTests, VectorTraversal) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Using iterators to traverse the vector
    int sum = 0;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        sum += *it;
    }

    // The sum of all elements should be 15 (1+2+3+4+5)
    ASSERT_EQ(sum, 15);
}

// Advanced test 1: Modify vector elements using iterators
TEST(IteratorTests, ModifyVector) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Using iterators to double each element in the vector
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        *it *= 2;
    }

    // After modification, the vector should be {2, 4, 6, 8, 10}
    ASSERT_EQ(numbers, std::vector<int>{2, 4, 6, 8, 10});
}

// Advanced test 2: Lookup specific elements using iterators
TEST(IteratorTests, GetElementLookup) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Using iterators to access specific elements
    auto it = numbers.begin();
    ASSERT_EQ(*it, 1);
    std::advance(it, 2);
    ASSERT_EQ(*it, 3);
}

// Advanced test 3: Check if iterators can handle an empty vector
TEST(IteratorTests, EmptyVector) {
    std::vector<int> emptyVec;

    // Ensure iterators work correctly with an empty vector
    ASSERT_EQ(emptyVec.begin(), emptyVec.end());
}

// Advanced test 4: Find and erase element using iterators
TEST(IteratorTests, FindAndErase) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Using iterators to find and erase an element (e.g., erase 3)
    auto it = std::find(numbers.begin(), numbers.end(), 3);
    if (it != numbers.end()) {
        numbers.erase(it);
    }

    // After erasing, the vector should be {1, 2, 4, 5}
    ASSERT_EQ(numbers, std::vector<int>{1, 2, 4, 5});
}

// Advanced test 5: Reverse the order of elements using iterators
TEST(IteratorTests, ReverseOrder) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Using iterators to reverse the order of elements in the vector
    std::reverse(numbers.begin(), numbers.end());

    // After reversing, the vector should be {5, 4, 3, 2, 1}
    ASSERT_EQ(numbers, std::vector<int>{5, 4, 3, 2, 1});
}

// Advanced test 6: Use iterators with algorithms (accumulate)
TEST(IteratorTests, IteratorWithAlgorithm) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Using iterators with algorithms (accumulate to find the sum)
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

    // The sum of all elements should be 15 (1+2+3+4+5)
    ASSERT_EQ(sum, 15);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
