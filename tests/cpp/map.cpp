#include <gtest/gtest.h>
#include <map>

// Best Used For: Associative containers that store key-value pairs in a sorted order based on the keys.
//
// Best Use Cases:
// Maintaining a sorted collection of key-value pairs.
// Efficient lookups and retrieval based on keys.
// When the order of insertion is important.

TEST(MapTests, BasicUsage)
{
    std::map<int, std::string> myMap;
    myMap[1] = "one";

    // Check if the map contains the expected element
    EXPECT_EQ(myMap[1], "one");
}

TEST(MapAdvancedTests, IteratorAndErase)
{
    std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};

    // Erase elements with keys less than 3
    for (auto it = myMap.begin(); it != myMap.end();)
    {
        if (it->first < 3)
        {
            it = myMap.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Check if the map is modified as expected
    EXPECT_EQ(myMap.size(), 1);
    EXPECT_EQ(myMap[3], "three");
}

TEST(MapAdvancedTests, MultiMap)
{
    std::multimap<char, std::string> myMultiMap;

    // Insert multiple elements with the same key
    myMultiMap.insert(std::make_pair('a', "apple"));
    myMultiMap.insert(std::make_pair('a', "avocado"));
    myMultiMap.insert(std::make_pair('b', "banana"));

    // Check the number of elements with key 'a'
    EXPECT_EQ(myMultiMap.count('a'), 2);
}

TEST(MapAdvancedTests, Emplace)
{
    std::map<int, std::string> myMap;

    // Emplace elements directly into the map
    myMap.emplace(1, "one");
    myMap.emplace_hint(myMap.begin(), 2, "two");

    // Check if the map contains the expected elements
    EXPECT_EQ(myMap.size(), 2);
}

// Advanced level test: Showcase various member functions of std::map
TEST(MapAdvancedTests, AllMemberFunctions)
{
    // Create a map with some initial elements
    std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};

    // Access begin and end iterators
    auto beginIt = myMap.begin();
    auto endIt = myMap.end();

    // Use std::distance to calculate the size using iterators
    size_t mapSize = static_cast<size_t>(std::distance(beginIt, endIt));
    EXPECT_EQ(mapSize, 3);

    // Use std::advance to move the iterator to the middle
    std::advance(beginIt, mapSize / 2);

    // Insert an element before the iterator position
    myMap.insert(beginIt, std::make_pair(4, "four"));

    // Check if the map is modified as expected
    auto rhs = std::map<int, std::string>{{1, "one"}, {2, "two"}, {4, "four"}, {3, "three"}};
    EXPECT_EQ(myMap, rhs);

    // Erase an element at a specific position
    myMap.erase(beginIt);

    // Check if the map is modified as expected
    rhs = std::map<int, std::string>{{1, "one"}, {4, "four"}, {3, "three"}};
    EXPECT_EQ(myMap, rhs);

    // Access elements using operator[]
    std::string &element = myMap[4];
    element += " updated";

    // Check if the map is modified as expected
    EXPECT_EQ(myMap[4], "four updated");

    // Find an element in the map
    auto findIt = myMap.find(1);

    // Check if the element is found
    EXPECT_NE(findIt, myMap.end());
    EXPECT_EQ(findIt->second, "one");

    // Count occurrences of a key
    size_t count = myMap.count(4);
    EXPECT_EQ(count, 1);

    // Lower and upper bound for a key
    auto lower = myMap.lower_bound(2);
    auto upper = myMap.upper_bound(2);

    for (const auto &pair : myMap)
    {
        std::cout << "{" << pair.first << ": " << pair.second << "} ";
    }

    // Check if the bounds are as expected
    EXPECT_EQ(lower->first, 3);
    EXPECT_EQ(upper->first, 3);

    // Equal range for a key
    auto range = myMap.equal_range(3);

    // Check if the range includes the expected key
    EXPECT_NE(range.first, myMap.end());
    EXPECT_EQ(range.first->first, 3);
    EXPECT_NE(range.second, myMap.end());
    EXPECT_EQ(range.second->first, 4);

    // Clear the map
    myMap.clear();

    // Check if the map is cleared
    EXPECT_TRUE(myMap.empty());
}
