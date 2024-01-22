/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <iostream>
#include <gtest/gtest.h> // Google Test framework

class ComplexObject
{
public:
    ComplexObject() : value(0), multiplier(0.0) {} // Default constructor
    ComplexObject(int val, double factor) : value(val), multiplier(factor) {}
    double calculateResult() const { return value * multiplier; }

private:
    int value;
    double multiplier;
};

// Custom allocator definition
template <typename T>
class CustomAllocator
{
public:
    /**
     * The T *allocate(size_t size) function uses the new operator to allocate a dynamic array
     * of objects of type T. The expression new T[size] allocates memory for an array of size objects
     *  of type T and returns a pointer to the first element of that array.
     *
     * new T[size]: Allocates memory for an array of size objects of type T.
     * T *: The result is a pointer to the first element of the allocated array.
     */
    T *allocate(size_t size)
    {
        return new T[size];
    }

    void deallocate(T *ptr, size_t size)
    {
        delete[] ptr;
    }

    // Calculate and return the overhead for a given allocation
    size_t overhead(T *ptr, size_t requestedSize) const
    {
        // Calculate the actual allocated size
        size_t allocatedSize = calculateAllocatedSize(ptr);

        // Calculate the overhead
        return (allocatedSize > requestedSize) ? (allocatedSize - requestedSize) : 0;
    }

    /**
     * Args &&...args:
     *
     * This is a variadic template parameter pack named args using universal references (&&).
     * Universal references are declared using && and can bind to both lvalues and rvalues. In this context,
     * it allows the construct function to accept a variable number of arguments of any type.
     *
     * std::forward<Args>(args)...:
     *
     * This is the perfect forwarding part. It uses std::forward to forward the
     * arguments exactly as they were passed to the construct function. The ... at the end is the parameter
     * pack expansion, which essentially unpacks the arguments.
     */
    template <typename... Args>
    void construct(T *ptr, Args &&...args) // This is a variadic template parameter pack
    {
        new (ptr) T(std::forward<Args>(args)...);
    }

    void destroy(T *ptr)
    {
        ptr->~T();
    }

private:
    // Helper function to calculate the actual allocated size of an object
    size_t calculateAllocatedSize(T *ptr) const
    {
        // This is a simplistic example; adjust based on your allocator's internal bookkeeping
        // For illustration purposes, assuming a simple fixed-size allocation
        return sizeof(T);
    }
};

// Fixture class for common setup and teardown
class CustomAllocatorTest : public ::testing::Test
{
protected:
    CustomAllocator<ComplexObject> myAllocator;

    void SetUp() override
    {
        // Additional setup code, if any
    }

    void TearDown() override
    {
        // Additional teardown code, if any
    }
};

TEST_F(CustomAllocatorTest, AllocatingAndInitializing)
{
    ComplexObject *obj = myAllocator.allocate(1);

    ASSERT_NE(obj, nullptr);

    // Construct the object
    myAllocator.construct(obj, 5, 2.5);

    // Check the result
    ASSERT_EQ(obj->calculateResult(), 12.5);

    // Destroy the object before deallocating the memory
    myAllocator.destroy(obj);

    // Deallocate the memory after destroying the object
    myAllocator.deallocate(obj, 1);
}

TEST_F(CustomAllocatorTest, AllocatingAndCopying)
{
    ComplexObject *obj1 = myAllocator.allocate(1);
    ASSERT_NE(obj1, nullptr);
    myAllocator.construct(obj1, 5, 2.5);

    ComplexObject *obj2 = myAllocator.allocate(1);
    ASSERT_NE(obj2, nullptr);
    myAllocator.construct(obj2, *obj1);

    ASSERT_EQ(obj2->calculateResult(), obj1->calculateResult());

    myAllocator.destroy(obj1);
    myAllocator.destroy(obj2);

    myAllocator.deallocate(obj1, 1);
    myAllocator.deallocate(obj2, 1);
}

TEST_F(CustomAllocatorTest, MemoryReuseWithDifferentTypes)
{
    CustomAllocator<int> intAllocator;

    int *data = intAllocator.allocate(3);
    ASSERT_NE(data, nullptr);
    intAllocator.deallocate(data, 3);

    ComplexObject *obj = myAllocator.allocate(2);
    ASSERT_NE(obj, nullptr);
    myAllocator.deallocate(obj, 2);
}

TEST_F(CustomAllocatorTest, VerifyAlignmentAndOverhead)
{
    const size_t dataSize = 1000; // Adjust based on your specific needs

    // Allocate memory for objects of various sizes
    ComplexObject *data1 = myAllocator.allocate(dataSize);

    // Note: Adjust the type of data2 and data3 based on your actual implementation
    ComplexObject *data2 = myAllocator.allocate(dataSize * 2);
    ComplexObject *data3 = myAllocator.allocate(dataSize * 3);

    // Check alignment for each allocated memory block
    const size_t alignmentRequirement = alignof(double); // Adjust based on your custom allocator's alignment requirements

    EXPECT_EQ(reinterpret_cast<uintptr_t>(data1) % alignmentRequirement, 0);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(data2) % alignmentRequirement, 0);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(data3) % alignmentRequirement, 0);

    // Check overhead by comparing allocated size with requested size
    const size_t overheadThreshold = 16; // Adjust based on your specific expectations for overhead

    EXPECT_LE(myAllocator.overhead(data1, dataSize), overheadThreshold);
    EXPECT_LE(myAllocator.overhead(data2, dataSize * 2), overheadThreshold);
    EXPECT_LE(myAllocator.overhead(data3, dataSize * 3), overheadThreshold);

    // Deallocate memory using the correct allocator
    CustomAllocator<ComplexObject> charAllocator;
    charAllocator.deallocate(data1, dataSize);
    charAllocator.deallocate(data2, dataSize * 2);
    charAllocator.deallocate(data3, dataSize * 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
