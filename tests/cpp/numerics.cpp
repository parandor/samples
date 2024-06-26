#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <limits.h>
#include <cmath>

using namespace std;

namespace Numerics
{
    class Numerics
    {
    public:
        /**
         * Reverses digits given an input integer using recursion.
         * Returns the reversed digits of given integer.
         * TODO: Support integers ending in zeros.
         * TODO: Support reversing integers ending in zeros.
         * @param in Input integer
         * @param out Partially reversed integer used in recusion
         * @return T Reversed integer result.
         */
        template <typename T>
        static T reverseDigitsRecursive(const T &in, const T &out = 0)
        {
            const T input = std::move(in);
            if (input == 0)
            {
                return out;
            }
            const T &rem = input % 10;
            return reverseDigitsRecursive((input - rem) / 10, out * 10 + rem);
        }

        /**
         * Reverses digits given an input integer. Non-recursive.
         * Note: Will return reversed string of digits, excluding sign.
         * Reason for returning string is that integer values
         * cannot keep zeros, eg: 007 will be stored as 7 in an integer.
         * Exluded sign to simplify internal logic.
         * @param in Input integer
         * @return string Reversed integer result.
         *
         */
        template <typename T>
        static string reverseDigits(const T &in)
        {
            // Perform assertions, error checking, or throw
            if (std::isnan(in))
                return "";
            if (!std::numeric_limits<T>::is_integer)
                return "";
            if (in == 0)
                return "0";

            T in_copy = std::move(in);
            // Track count of post zeros, eg: 1000 would be 3 zeros. Will be added at the end
            unsigned count = 0;
            while (in_copy % 10 == 0)
            {
                count++;
                in_copy /= 10;
            }

            long long reversed_number = 0, remainder;
            T input = std::move(in);
            // Reverse numbers using remainder arithmetic
            while (input != 0)
            {
                remainder = input % 10;
                reversed_number = reversed_number * 10 + remainder;
                input /= 10;
            }

            string out = to_string(reversed_number);

            // Account for zeros and prepend all
            while (count-- > 0)
                out = "0" + out;
            return out;
        }
    };

    template <typename T>
    void checkReverseDigits(const T &min, const T &max)
    {
        T value = min;
        for (;;)
        {
            long long value_pos = static_cast<long long>(value);
            // Cast to positive to work with positive values
            if (value < 0)
            {
                value_pos = -value_pos;
            }
            // Reverse integer using string
            string expected = to_string(value_pos);
            reverse(expected.begin(), expected.end());

            // Reverse digits and assert
            string actual = Numerics::reverseDigits(value_pos);
            ASSERT_EQ(expected, actual);
            if (value++ == max)
                break;
        }
    }

    TEST(NumericsTests, NumericsReverseDigitsShort)
    {
        checkReverseDigits(SHRT_MIN, SHRT_MAX);
    }

    TEST(NumericsTests, NumericsReverseDigitsChar)
    {
        checkReverseDigits(CHAR_MIN, CHAR_MAX);
    }

    // TODO: Very long test. Use sparingly.
    // TEST(NumericsTests, NumericsReverseDigitsInt)
    // {
    //     checkReverseDigits(INT_MIN, INT_MAX);
    // }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
