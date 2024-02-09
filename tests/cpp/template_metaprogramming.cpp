#include <gtest/gtest.h>

// Template metaprogramming is a technique where templates are used to perform computations at compile-time.
// This allows for powerful abstraction and manipulation of types and values, enabling tasks such as
// compile-time calculations, type introspection, and code generation. It is often used in libraries
// and frameworks where performance and flexibility are critical, such as in generic programming
// libraries, embedded systems, and template-based libraries like the C++ Standard Library.

// Template metaprogramming can offer performance benefits in several ways:
// Compile-time computation: Template metaprogramming allows certain computations to be performed 
// at compile time rather than at runtime. This can eliminate the need for runtime calculations, 
// leading to faster program execution. For example, in the provided code, factorial, Fibonacci 
// sequence generation, and square root calculations are all performed at compile time, reducing the 
// workload on the runtime environment.

// Optimized code generation: Template metaprogramming can enable the generation of highly optimized 
// code tailored to specific types or values. By leveraging compile-time information, the compiler can 
// generate code that is specialized for the particular use case, potentially resulting in more 
// efficient code compared to runtime polymorphism or dynamic dispatch.

// Reduced runtime overhead: Template metaprogramming can eliminate runtime overhead associated with 
// dynamic dispatch or virtual function calls. Instead of relying on runtime polymorphism, where the
// decision about which function to call is made at runtime, template metaprogramming resolves such 
// decisions at compile time, leading to direct function invocations without the need for runtime 
// dispatch mechanisms.

// Inlining opportunities: Templates facilitate inlining of code at compile time. When templates are 
// instantiated with specific types or values, the compiler can often inline the generated code directly 
// at the call site, eliminating function call overhead and potentially enabling further optimizations 
// such as constant folding and dead code elimination.

// Reduced runtime dependencies: Template metaprogramming can lead to code that is less dependent on
// runtime libraries or dynamic memory allocation. This can result in smaller binary sizes and reduced
// runtime memory footprint, which can be beneficial in resource-constrained environments such as 
// embedded systems or high-performance computing.

// 1. Basic template metaprogramming: Factorial calculation
template <int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
    static constexpr int value = 1;
};

TEST(TemplateMetaprogramming, Factorial) {
    EXPECT_EQ(Factorial<0>::value, 1);
    EXPECT_EQ(Factorial<1>::value, 1);
    EXPECT_EQ(Factorial<5>::value, 120);
    EXPECT_EQ(Factorial<10>::value, 3628800);
}

// 2. Compile-time Fibonacci sequence generation
template<int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

TEST(TemplateMetaprogramming, Fibonacci) {
    EXPECT_EQ(Fibonacci<0>::value, 0);
    EXPECT_EQ(Fibonacci<1>::value, 1);
    EXPECT_EQ(Fibonacci<5>::value, 5);
    EXPECT_EQ(Fibonacci<10>::value, 55);
}

// 3. Type traits: Checking if a type is a pointer
template<typename T>
struct IsPointer {
    static constexpr bool value = false;
};

template<typename T>
struct IsPointer<T*> {
    static constexpr bool value = true;
};

TEST(TemplateMetaprogramming, IsPointer) {
    EXPECT_FALSE(IsPointer<int>::value);
    EXPECT_TRUE(IsPointer<int*>::value);
    EXPECT_TRUE(IsPointer<double*>::value);
    EXPECT_FALSE(IsPointer<float>::value);
}

// 4. Compile-time integer square root calculation
template<int N, int LO = 0, int HI = N>
struct Sqrt {
    static constexpr int mid = (LO + HI + 1) / 2;
    static constexpr int value = (LO > HI) ? HI : (N < mid * mid) ? Sqrt<N, LO, mid - 1>::value : Sqrt<N, mid, HI>::value;
};

template<int N, int VAL>
struct Sqrt<N, VAL, VAL> {
    static constexpr int value = VAL;
};

TEST(TemplateMetaprogramming, Sqrt) {
    EXPECT_EQ(Sqrt<0>::value, 0);
    EXPECT_EQ(Sqrt<1>::value, 1);
    EXPECT_EQ(Sqrt<16>::value, 4);
    EXPECT_EQ(Sqrt<25>::value, 5);
    EXPECT_EQ(Sqrt<100>::value, 10);
}

// 5. Compile-time string manipulation: Concatenation
template<typename T, T... chars>
struct StringHolder {
    static constexpr char value[] = {chars..., '\0'};
};

template<typename T, T... chars>
constexpr char StringHolder<T, chars...>::value[];

template<typename String1, typename String2>
struct ConcatenateStrings;

template<typename T, T... chars1, T... chars2>
struct ConcatenateStrings<StringHolder<T, chars1...>, StringHolder<T, chars2...>> {
    using type = StringHolder<T, chars1..., chars2...>;
};

template<typename String1, typename String2>
using ConcatenateStrings_t = typename ConcatenateStrings<String1, String2>::type;

TEST(TemplateMetaprogramming, ConcatenateStrings) {
    using Str1 = StringHolder<char, 'H', 'e', 'l', 'l', 'o', ',', ' '>;
    using Str2 = StringHolder<char, 'w', 'o', 'r', 'l', 'd', '!', '\0'>;
    constexpr auto result = ConcatenateStrings_t<Str1, Str2>::value;
    EXPECT_STREQ(result, "Hello, world!");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
