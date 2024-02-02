#include <gtest/gtest.h>
#include <set>

// Best Used For: Storing unique elements in a sorted order.
//
// Best Use Cases:
// Maintaining a sorted collection of unique elements.
// Efficient membership check (finding if an element is present).
// When elements need to be in sorted order without associated values.

namespace
{
    TEST(SetTests, BasicUsage)
    {
        std::set<int> mySet;
        mySet.insert(42);

        // Check if the set contains the expected element
        EXPECT_EQ(*mySet.begin(), 42);
    }

    TEST(SetAdvancedTests, EraseAndFind)
    {
        std::set<int> mySet = {3, 1, 4, 1, 5};

        // Erase elements with value 1
        mySet.erase(1);

        // Find element with value 4
        auto it = mySet.find(4);

        // Check if the set is modified as expected
        EXPECT_EQ(mySet.size(), 3);
        EXPECT_NE(it, mySet.end());
    }

    TEST(SetAdvancedTests, CustomComparator)
    {
        struct CustomComparator
        {
            bool operator()(const std::string &a, const std::string &b) const
            {
                return a.length() < b.length();
            }
        };

        std::set<std::string, CustomComparator> mySet = {"apple", "orange", "banana"};

        // Check if the set is sorted based on string length
        EXPECT_EQ(*mySet.begin(), "apple");
        EXPECT_EQ(*mySet.rbegin(), "orange");
    }

    TEST(SetAdvancedTests, LowerAndUpperBound)
    {
        std::set<int> mySet = {10, 20, 30, 40, 50};

        // Find lower and upper bounds for value 25
        auto lower = mySet.lower_bound(25);
        auto upper = mySet.upper_bound(25);

        // Check if the bounds are as expected
        EXPECT_EQ(*lower, 30);
        EXPECT_EQ(*upper, 30);
    }

    // Advanced level test: Showcase various member functions of std::set
    TEST(SetAdvancedTests, AllMemberFunctions)
    {
        // Create a set with some initial elements
        std::set<int> mySet = {1, 2, 3, 4, 5};

        // Access begin and end iterators
        auto beginIt = mySet.begin();
        auto endIt = mySet.end();

        // Use std::distance to calculate the size using iterators
        size_t setSize = static_cast<size_t>(std::distance(beginIt, endIt));
        EXPECT_EQ(setSize, 5);

        // Insert an element
        mySet.insert(6);

        // Check if the set is modified as expected
        auto rhs = std::set<int>{1, 2, 3, 4, 5, 6};
        EXPECT_EQ(mySet, rhs);

        // Erase an element
        mySet.erase(4);

        rhs = std::set<int>{1, 2, 3, 5, 6};
        // Check if the set is modified as expected
        EXPECT_EQ(mySet, rhs);

        // Find an element in the set
        auto findIt = mySet.find(3);

        // Check if the element is found
        EXPECT_NE(findIt, mySet.end());
        EXPECT_EQ(*findIt, 3);

        // Count occurrences of a key
        size_t count = mySet.count(5);
        EXPECT_EQ(count, 1);

        // Lower and upper bound for a key
        auto lower = mySet.lower_bound(2);
        auto upper = mySet.upper_bound(2);

        // Check if the bounds are as expected
        EXPECT_EQ(*lower, 2);
        EXPECT_EQ(*upper, 3);

        // Equal range for a key
        auto range = mySet.equal_range(3);

        // Check if the range includes the expected key
        EXPECT_NE(range.first, mySet.end());
        EXPECT_EQ(*range.first, 3);
        EXPECT_NE(range.second, mySet.end());
        EXPECT_EQ(*range.second, 5);

        // Clear the set
        mySet.clear();

        // Check if the set is cleared
        EXPECT_TRUE(mySet.empty());
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}