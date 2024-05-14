#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

void printOccurrences(int *arr, int n)
{
    if (arr == nullptr)
    {
        return;
    }

    unordered_map<int, int> map;
    for (int i = 0; i < n; ++i)
    {
        map[arr[i]]++;
    }
}

set<int> unique(int *arr, int n)
{
    if (arr == nullptr)
    {
        return set<int>({});
    }
    int unique[] = {};
    return set<int>(arr, arr + n);;
}

set<int> unique(const vector<int> &vec)
{
    if (vec.empty())
    {
        return set<int>({});
    }
    int unique[] = {};
    return set<int>(vec.begin(), vec.end());
}

/**
 * Count occurences and remove duplicates in place without copies of vector
 */
template <typename T>
std::unordered_map<T, int> countOccurencesAndRemoveDuplicates(vector<T> &vec)
{
    std::unordered_map<T, int> map;

    // Iterate over the vector to count occurrences and remove duplicates
    vec.erase(std::remove_if(vec.begin(), vec.end(), [&](T c)
                             {
        if (map[c] > 0) {
            return true; // remove duplicate
        } else {
            map[c]++;
            return false;
        } }),
              vec.end());
    return map;
}

template <typename T>
unordered_map<T, int> countDuplicates(vector<T> &vec)
{
    unordered_map<T, int> map;
    for (const auto &item : vec)
    {
        map[item]++;
    }
    return map;
}

TEST(OccurencesTests, CountAndValidateDuplicates)
{
    vector<char> actual = {'a', 'b', 'c', 'a', 'd', 'b', 'e', 'a', 'c', 'f', 'f', 'f'};
    unordered_map<char, int> map = countDuplicates(actual);
    unordered_map<char, int> expected = {{'a', 3}, {'b', 2}, {'c', 2}, {'d', 1}, {'e', 1}, {'f', 3}};

    // Print the elements of the vector without duplicates
    for (auto item : expected)
    {
        // Find the expected char in the duplicates map DS. Iter should not reach end.
        auto it = map.find(item.first);
        ASSERT_NE(it, map.end());
        // Check the expected char count against the duplicates map DS.
        ASSERT_EQ(item.second, map[item.first]);
    }
}

TEST(OccurencesTests, CountOccurencesAndRemoveDuplicates)
{
    std::vector<char> actual = {'a', 'b', 'c', 'a', 'd', 'b', 'e', 'a', 'c', 'f', 'f', 'f'};
    std::vector<char> expected = {'a', 'b', 'c', 'd', 'e', 'f'};
    unordered_map<char, int> map = countOccurencesAndRemoveDuplicates(actual);

    // Print the elements of the vector without duplicates
    for (int i = 0; i < expected.size(); ++i)
    {
        ASSERT_EQ(actual.at(i), expected.at(i));
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int arr[] = {1, 2, 3, 4, 1, 2, 3, 1, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printOccurrences(arr, n);
    unique(arr, n);

    vector<int> vec = {1, 2, 3, 4, 1, 2, 3, 1, 2, 1};
    unique(vec);

    return RUN_ALL_TESTS();
}
