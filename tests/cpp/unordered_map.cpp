#include <gtest/gtest.h>
#include <unordered_map>

// Best Used For: Associative containers that store key-value pairs without any specific order.
//
// Best Use Cases:
// When the order of elements doesn't matter.
// Efficient lookups and retrieval based on keys.
// Handling large datasets with a good hash function to minimize collisions.

TEST(UnorderedMapTests, BasicUsage)
{
    std::unordered_map<int, std::string> myUnorderedMap;
    myUnorderedMap[1] = "one";

    // Check if the unordered map contains the expected element
    EXPECT_EQ(myUnorderedMap[1], "one");
}

TEST(UnorderedMapAdvancedTests, BucketCountAndRehash)
{
    std::unordered_map<int, std::string> myUnorderedMap;

    // Reserve space for at least 50 elements
    myUnorderedMap.reserve(50);

    // Check the initial bucket count
    size_t initialBucketCount = myUnorderedMap.bucket_count();

    // Insert elements to trigger a rehash
    for (int i = 0; i < 100; ++i)
    {
        myUnorderedMap[i] = "value" + std::to_string(i);
    }

    // Check if the bucket count has increased after rehash
    EXPECT_GT(myUnorderedMap.bucket_count(), initialBucketCount);
}

TEST(UnorderedMapAdvancedTests, LoadFactor)
{
    std::unordered_map<int, std::string> myUnorderedMap;

    // Set a custom load factor threshold
    myUnorderedMap.max_load_factor(0.5);

    // Insert elements to exceed the load factor threshold
    for (int i = 0; i < 10; ++i)
    {
        myUnorderedMap[i] = "value" + std::to_string(i);
    }

    // Check if the load factor is within the threshold
    EXPECT_LE(myUnorderedMap.load_factor(), myUnorderedMap.max_load_factor());
}

TEST(UnorderedMapAdvancedTests, BucketIterator)
{
    std::unordered_map<int, std::string> myUnorderedMap = {{1, "one"}, {2, "two"}, {3, "three"}};

    // Iterate over buckets and count non-empty buckets
    size_t nonEmptyBuckets = 0;
    for (size_t i = 0; i < myUnorderedMap.bucket_count(); ++i)
    {
        if (myUnorderedMap.bucket_size(i) > 0)
        {
            ++nonEmptyBuckets;
        }
    }

    // Check if the number of non-empty buckets is as expected
    EXPECT_EQ(nonEmptyBuckets, 3);
}

// Advanced level test: Showcase various member functions of std::unordered_map
TEST(UnorderedMapAdvancedTests, AllMemberFunctions)
{
    // Create an unordered_map with some initial elements
    std::unordered_map<int, std::string> myUnorderedMap = {{1, "one"}, {2, "two"}, {3, "three"}};

    // Access begin and end iterators
    auto beginIt = myUnorderedMap.begin();
    auto endIt = myUnorderedMap.end();

    // Use std::distance to calculate the size using iterators
    size_t mapSize = static_cast<size_t>(std::distance(beginIt, endIt));
    EXPECT_EQ(mapSize, 3);

    // Insert an element
    myUnorderedMap.insert({4, "four"});

    // Check if the unordered_map is modified as expected
    auto rhs = std::unordered_map<int, std::string>{{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
    EXPECT_EQ(myUnorderedMap, rhs);

    // Erase an element
    myUnorderedMap.erase(2);

    // Check if the unordered_map is modified as expected
    rhs = std::unordered_map<int, std::string>{{1, "one"}, {3, "three"}, {4, "four"}};
    EXPECT_EQ(myUnorderedMap, rhs);

    // Find an element in the unordered_map
    auto findIt = myUnorderedMap.find(3);

    // Check if the element is found
    EXPECT_NE(findIt, myUnorderedMap.end());
    EXPECT_EQ(findIt->second, "three");

    // Count occurrences of a key (since unordered_map does not allow duplicates, count is either 0 or 1)
    size_t count = myUnorderedMap.count(4);
    EXPECT_EQ(count, 1);

    // Access elements using operator[]
    myUnorderedMap[5] = "five";

    // Check if the unordered_map is modified as expected
    rhs = std::unordered_map<int, std::string>{{1, "one"}, {3, "three"}, {4, "four"}, {5, "five"}};
    EXPECT_EQ(myUnorderedMap, rhs);

    // Clear the unordered_map
    myUnorderedMap.clear();

    // Check if the unordered_map is cleared
    EXPECT_TRUE(myUnorderedMap.empty());
}
