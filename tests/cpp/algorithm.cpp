/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <algorithm>
#include <limits.h>
#include <vector>
#include <numeric>
#include <gtest/gtest.h>
#include <chrono>

using namespace std;
using namespace chrono;

namespace
{
    // Google Test example for find_if
    TEST(AlgorithmTests, FindIfEvenTest)
    {
        vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        // Test if find_if can find the first even number
        auto result = find_if(numbers.begin(), numbers.end(), [](int n)
                              { return n % 2 == 0; });
        ASSERT_NE(result, numbers.end());
        EXPECT_EQ(*result, 2);
    }

    // Google Test example for sort
    TEST(AlgorithmTests, SortTest)
    {
        vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 10, 6};

        // Test if sort can arrange numbers in ascending order
        sort(numbers.begin(), numbers.end());
        vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        EXPECT_EQ(numbers, expected);
    }

    // Google Test example for accumulate
    TEST(AlgorithmTests, AccumulateTest)
    {
        vector<int> numbers = {1, 2, 3, 4, 5};

        // Test if accumulate can sum the numbers
        int sum = accumulate(numbers.begin(), numbers.end(), 0);
        EXPECT_EQ(sum, 15);
    }

    // Sorting Test
    TEST(AlgorithmTests, SortingTest)
    {
        vector<int> numbers = {4, 2, 7, 1, 9};
        sort(numbers.begin(), numbers.end());
        auto rhs = vector<int>{1, 2, 4, 7, 9};
        ASSERT_EQ(numbers, rhs);
    }

    // Searching Test
    TEST(AlgorithmTests, SearchingTest)
    {
        vector<int> numbers = {1, 2, 4, 7, 9};
        auto it = find(numbers.begin(), numbers.end(), 4);
        ASSERT_NE(it, numbers.end());
        ASSERT_EQ(*it, 4);
    }

    // Transform Test
    TEST(AlgorithmTests, TransformTest)
    {
        vector<int> numbers = {1, 2, 3, 4, 5};
        transform(numbers.begin(), numbers.end(), numbers.begin(), [](int n)
                  { return n * 2; });
        auto rhs = vector<int>{2, 4, 6, 8, 10};
        ASSERT_EQ(numbers, rhs);
    }

    // Accumulation Test
    TEST(AlgorithmTests, AccumulationTest)
    {
        vector<int> numbers = {1, 2, 3, 4, 5};
        int sum = accumulate(numbers.begin(), numbers.end(), 0);
        ASSERT_EQ(sum, 15);
    }

    // Unique Test
    TEST(AlgorithmTests, UniqueTest)
    {
        vector<int> numbers = {1, 2, 2, 3, 4, 4, 4, 5};
        auto newEnd = unique(numbers.begin(), numbers.end());
        numbers.erase(newEnd, numbers.end());
        auto rhs = vector<int>{1, 2, 3, 4, 5};
        ASSERT_EQ(numbers, rhs);
    }

    // Additional Test: Reverse Test
    TEST(AlgorithmTests, ReverseTest)
    {
        vector<int> numbers = {1, 2, 3, 4, 5};
        reverse(numbers.begin(), numbers.end());
        auto rhs = vector<int>{5, 4, 3, 2, 1};
        ASSERT_EQ(numbers, rhs);
    }

    // Additional Test: Fill Test
    TEST(AlgorithmTests, FillTest)
    {
        vector<int> numbers(5);
        fill(numbers.begin(), numbers.end(), 42);
        auto rhs = vector<int>{42, 42, 42, 42, 42};
        ASSERT_EQ(numbers, rhs);
    }

    // Additional Test: Count Test
    TEST(AlgorithmTests, CountTest)
    {
        vector<int> numbers = {1, 2, 2, 3, 4, 4, 4, 5};
        int count = std::count(numbers.begin(), numbers.end(), 4);
        ASSERT_EQ(count, 3);
    }

    std::string padString(const std::string &str, size_t length)
    {
        // Calculate the number of characters to pad
        size_t padding = length - str.length();

        // Return the padded string
        return str + std::string(padding, '0');
    }

    std::pair<std::string, std::string> padStrings(const std::string &str1, const std::string &str2)
    {
        // Find the maximum length among the two strings
        size_t maxLength = std::max(str1.length(), str2.length());

        // Pad both strings to the maximum length
        std::string paddedStr1 = padString(str1, maxLength);
        std::string paddedStr2 = padString(str2, maxLength);

        // Return the pair of padded strings
        return std::make_pair(paddedStr1, paddedStr2);
    }

    /**
     * Definition for singly-linked list.
     */
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    class Solution
    {
    public:
        /**
         * You are given two non-empty linked lists representing two non-negative integers.
         * The digits are stored in reverse order, and each of their nodes contains a single
         *  digit. Add the two numbers and return the sum as a linked list.
         * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
         */
        ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
        {
            ListNode *list = l1;
            string num1, num2;
            while (true)
            {
                num1 += to_string(list->val);
                list = list->next;
                if (list == NULL)
                {
                    break;
                }
            }
            list = l2;
            while (true)
            {
                num2 += to_string(list->val);
                list = list->next;
                if (list == NULL)
                {
                    break;
                }
            }
            auto paddedStrings = padStrings(num1, num2);
            string num_res = "";
            bool carry = false;
            for (int i = 0; i < paddedStrings.first.size(); ++i)
            {
                int first = paddedStrings.first[i] - '0';
                int second = paddedStrings.second[i] - '0';
                int res = (first + second);
                if (carry)
                {
                    res++;
                    carry = false;
                }
                int digit = res % 10;
                num_res += to_string(digit);
                carry = res > 9;
            }
            if (carry)
            {
                num_res += "1";
                carry = false;
            }

            list = new ListNode(num_res[0] - '0');

            ListNode *list2return = list;
            for (int i = 1; i < num_res.size(); ++i)
            {
                list->next = new ListNode(num_res[i] - '0');
                list = list->next;
            }
            return list2return;
        }

        /**
         * You are given an array prices where prices[i] is the price of a given stock on the ith day.
         * You want to maximize your profit by choosing a single day to buy one stock and choosing a
         * different day in the future to sell that stock.
         * Return the maximum profit you can achieve from this transaction. If you cannot achieve any
         * profit, return 0.
         */
        template <typename T>
        T maxProfit(const vector<T> &prices)
        {
            T min = INT_MAX;
            T profit = 0;
            for (T i = 0; i < prices.size(); ++i)
            {
                if (prices[i] < min)
                {
                    min = prices[i];
                }
                profit = max(profit, prices[i] - min);
            }
            return profit;
        }

        /**
         * Given an array of integers nums and an integer target, return indices of the
         * two numbers such that they add up to target.
         * You may assume that each input would have exactly one solution, and you may
         * not use the same element twice.
         * You can return the answer in any order.
         */
        template <typename T>
        vector<T> twoSum(const vector<T> &nums, const T target)
        {
            vector<T> result = {-1, -1};
            unordered_map<T, T> map;
            for (T i = 0; i < nums.size(); ++i)
            {
                const T &complement = target - nums[i];
                if (map.find(complement) != map.end())
                {
                    result[0] = i;
                    result[1] = map[complement];
                    return result;
                }
                map[nums[i]] = i;
            }
            return result;
        }
    };

    TEST(AlgorithmTest, TwoSum)
    {
        vector<int> input = {3, 2, 4};
        vector<int> expected = {1, 2};
        int target = 6;
        Solution sol;
        vector<int> result = sol.twoSum(input, target);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        EXPECT_EQ(expected, result);
    }

    TEST(AlgorithmTest, MaxProfit)
    {
        vector<int> input = {7, 1, 5, 3, 6, 4};
        int expected = {5};
        Solution sol;
        int result = sol.maxProfit(input);
        EXPECT_EQ(expected, result);
        input = {7, 5, 3, 1, 1};
        expected = {0};
        result = sol.maxProfit(input);
        EXPECT_EQ(expected, result);
    }

    TEST(AlgorithmTest, AddTwoNumbers)
    {
        vector<int> l1 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
        vector<int> l2 = {6, 4};
        vector<int> expected = {6, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
        ListNode *ln1 = new ListNode(1);
        ListNode *ln1Ptr = ln1;
        for (auto a : l1)
        {
            ln1->next = new ListNode(a);
            ln1 = ln1->next;
        }
        ListNode *ln2 = new ListNode(5);
        ListNode *ln2Ptr = ln2;
        for (auto a : l2)
        {
            ln2->next = new ListNode(a);
            ln2 = ln2->next;
        }
        Solution sol;
        auto start = high_resolution_clock::now();
        ListNode *res = sol.addTwoNumbers(ln1Ptr, ln2Ptr);
        auto stop = high_resolution_clock::now();add t
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Run time: " << duration.count() << "us" << endl;
        for (int i = 0; i < expected.size(); ++i)
        {
            EXPECT_EQ(expected[i], res->val);
            res = res->next;
        }
    }

}
// Add more tests as needed

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}