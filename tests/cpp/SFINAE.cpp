#include <gtest/gtest.h> // Includes the Google Test framework header file.

#include <type_traits> // Includes the type_traits header file from the C++ Standard Library.
#include <vector> // Includes the vector header file from the C++ Standard Library.

// Define struct A with a member function foo
struct A { void foo() {} };
// Define struct B without a member function foo
struct B {};

// Example 1: Testing SFINAE with is_integral
// SFINAE (Substitution Failure Is Not An Error) is utilized here to enable the function only
// for integral types. The enable_if is used to enable the function if the provided type is
// integral; otherwise, the function is removed from the overload set during template
// instantiation. This prevents a compilation error when the function is called with
// non-integral types.
template<typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd(T i) {
    return i % 2 != 0;
}

// Example 2: Testing SFINAE with is_floating_point
// SFINAE is used to enable the function only for floating-point types. The enable_if is used
// to enable the function if the provided type is floating-point; otherwise, it is removed
// from the overload set.
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
is_positive(T i) {
    return i > 0;
}

// Example 3: Testing SFINAE with has_member
// SFINAE is used to check if a type has a member function named 'foo'. The enable_if is used
// to enable the struct template only if the test for the presence of 'foo' member function
// succeeds. If 'foo' member function is present, it resolves to a 'yes' type; otherwise, it
// resolves to a 'no' type, and SFINAE removes the overload from consideration.
template<typename T>
class has_member_foo {
    typedef char yes[1];
    typedef char no[2];

    template<typename C> static yes& test(decltype(&C::foo));
    template<typename C> static no& test(...);

    template<typename C>
    static constexpr bool check() {
        return sizeof(test<C>(0)) == sizeof(yes);
    }

public:
    static constexpr bool value = check<T>();
};

// Example 4: Testing SFINAE with is_container
// SFINAE is used to check if a type behaves like a container, i.e., it has 'begin' and 'end'
// member functions. The enable_if is used to enable the struct template only if the test for
// the presence of 'begin' and 'end' member functions succeeds. If 'begin' and 'end' member
// functions are present, the struct template resolves to a 'true_type'; otherwise, it
// resolves to a 'false_type', and SFINAE removes the overload from consideration.
template<typename T, typename = void>
struct is_container : std::false_type {};

template<typename T>
struct is_container<T,
    decltype(void(std::declval<T>().begin()),
             void(std::declval<T>().end()))> : std::true_type {};

// Example 5: Testing SFINAE with has_size_method
// SFINAE is used to check if a type has a member function named 'size'. The enable_if is
// used to enable the struct template only if the test for the presence of 'size' member
// function succeeds. If 'size' member function is present, it resolves to a 'true_type';
// otherwise, it resolves to a 'false_type', and SFINAE removes the overload from
// consideration.
template<typename T>
struct has_size_method {
private:
    template<typename C>
    static auto test(int) -> decltype(std::declval<C>().size(), std::true_type{});
    template<typename C>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

// GTest test case for SFINAE examples
TEST(SFINAETest, SFINAETests) {
    // Example 1: Testing SFINAE with is_integral
    EXPECT_TRUE(is_odd(3));
    // Compilation error expected: EXPECT_FALSE(is_odd(2.5));

    // Example 2: Testing SFINAE with is_floating_point
    EXPECT_TRUE(is_positive(3.5));
    // Compilation error expected: EXPECT_FALSE(is_positive(-2));

    // Example 3: Testing SFINAE with has_member
    EXPECT_TRUE(has_member_foo<A>::value);
    EXPECT_FALSE(has_member_foo<B>::value);

    // Example 4: Testing SFINAE with is_container
    EXPECT_TRUE(is_container<std::vector<int>>::value);
    EXPECT_FALSE(is_container<int>::value);

    // Example 5: Testing SFINAE with has_size_method
    EXPECT_TRUE(has_size_method<std::vector<int>>::value);
    EXPECT_FALSE(has_size_method<int>::value);
}

// Entry point for the program
int main(int argc, char **argv) {
    // Initializes the Google Test framework
    ::testing::InitGoogleTest(&argc, argv);
    // Runs all tests in the specified test cases and prints the results
    return RUN_ALL_TESTS();
}
