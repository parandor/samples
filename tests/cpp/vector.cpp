#include <gtest/gtest.h>
#include <vector>

// Best Used For:
// Sequences of elements where elements are frequently inserted or removed from the end.
//
// Best Use Cases:
// When dynamic resizing is not a concern.
// Iteration over elements in sequential order.
// Efficient random access to elements.

TEST(VectorTests, BasicUsage)
{
    std::vector<int> myVector;
    myVector.push_back(42);

    // Check if the vector contains the expected element
    EXPECT_EQ(myVector[0], 42);
}

// Advanced level tests
TEST(VectorAdvancedTests, Iteration)
{
    std::vector<int> myVector = {3, 1, 4, 1, 5};

    // Sum all elements using iterator
    int sum = 0;
    for (auto it = myVector.begin(); it != myVector.end(); ++it)
    {
        sum += *it;
    }

    EXPECT_EQ(sum, 14);
}

TEST(VectorAdvancedTests, ResizeAndAccess)
{
    std::vector<std::string> words(3, "hello");

    // Resize the vector and modify elements
    words.resize(5);
    words[4] = "world";

    EXPECT_EQ(words.back(), "world");
}

TEST(VectorAdvancedTests, InsertAndErase)
{
    std::vector<int> myVector = {1, 2, 3, 4, 5};

    // Insert an element at position 2
    myVector.insert(myVector.begin() + 2, 42);

    // Erase the element at position 4
    myVector.erase(myVector.begin() + 4);

    // Check if the vector is modified as expected
    EXPECT_EQ(myVector, std::vector<int>({1, 2, 42, 3, 5}));
}

TEST(VectorAdvancedTests, SwapAndClear)
{
    std::vector<int> vector1 = {1, 2, 3};
    std::vector<int> vector2 = {4, 5, 6};

    // Swap the contents of two vectors
    vector1.swap(vector2);

    // Clear the contents of one vector
    vector1.clear();

    EXPECT_TRUE(vector1.empty());
    EXPECT_EQ(vector2, std::vector<int>({1, 2, 3}));
}

TEST(VectorAdvancedTests, EmplaceAndEmplaceBack)
{
    std::vector<std::pair<int, std::string>> myVector;

    // Emplace elements directly into the vector
    myVector.emplace_back(1, "one");
    myVector.emplace_back(2, "two");

    // Check if the vector contains the expected elements
    EXPECT_EQ(myVector.size(), 2);
    EXPECT_EQ(myVector[0], std::make_pair(1, std::string("one")));
}

// Advanced level test: Showcase various member functions of std::vector
TEST(VectorAdvancedTests, AllMemberFunctions)
{
    // Create a vector with some initial elements
    std::vector<int> myVector = {1, 2, 3, 4, 5};

    // Access front and back elements
    EXPECT_EQ(myVector.front(), 1);
    EXPECT_EQ(myVector.back(), 5);

    // Access data as a pointer
    const int *dataPtr = myVector.data();
    EXPECT_EQ(dataPtr[2], 3);

    // Get iterator to the beginning and end
    std::vector<int>::iterator beginIt = myVector.begin();
    std::vector<int>::iterator endIt = myVector.end();

    // Use std::distance to calculate the size using iterators
    size_t vectorSize = static_cast<size_t>(std::distance(beginIt, endIt));
    EXPECT_EQ(vectorSize, 5);

    // Use std::advance to move the iterator to the middle
    std::advance(beginIt, vectorSize / 2);

    // Insert an element before the iterator position
    myVector.insert(beginIt, 42);

    // Check if the vector is modified as expected
    EXPECT_EQ(myVector, std::vector<int>({1, 2, 42, 3, 4, 5}));

    // Erase the element at the iterator position
    myVector.erase(myVector.begin() + 3);

    // Resize the vector to a new size
    myVector.resize(3);

    // Fill the vector with a specific value
    myVector.assign(3, 7);

    // Check if the vector is modified as expected
    EXPECT_EQ(myVector, std::vector<int>({7, 7, 7}));

    // Push elements to the back
    myVector.push_back(8);
    myVector.push_back(9);

    // Pop elements from the back
    myVector.pop_back();

    // Check if the vector is modified as expected
    EXPECT_EQ(myVector, std::vector<int>({7, 7, 7, 8}));

    // Resize the vector to a larger size
    myVector.resize(5, 10);

    // Check if the vector is modified as expected
    EXPECT_EQ(myVector, std::vector<int>({7, 7, 7, 8, 10}));

    // Swap the contents with another vector
    std::vector<int> otherVector = {1, 2, 3};
    myVector.swap(otherVector);

    // Check if the vectors are swapped as expected
    EXPECT_EQ(myVector, std::vector<int>({1, 2, 3}));
    EXPECT_EQ(otherVector, std::vector<int>({7, 7, 7, 8, 10}));

    // Clear the vector
    myVector.clear();

    // Check if the vector is cleared
    EXPECT_TRUE(myVector.empty());

    // Re-populate the vector
    myVector = {1, 2, 3, 4, 5, 6, 7};

    // Erase an element at a specific position
    myVector.erase(myVector.begin() + 2);

    // Check if the vector is modified as expected
    EXPECT_EQ(myVector, std::vector<int>({1, 2, 4, 5, 6, 7}));

    // Erase elements based on a condition (using erase_if)
    myVector.erase(std::remove_if(myVector.begin(), myVector.end(), [](int value)
                                  { return value % 2 == 0; }),
                   myVector.end());

    // Check if even elements are erased
    EXPECT_EQ(myVector, std::vector<int>({1, 5, 7}));

    // Using operators: Multiply each element by 2 using std::transform
    std::transform(myVector.begin(), myVector.end(), myVector.begin(), [](int value)
                   { return value * 2; });

    // Check if the vector is modified as expected
    EXPECT_EQ(myVector, std::vector<int>({2, 10, 14}));
}
