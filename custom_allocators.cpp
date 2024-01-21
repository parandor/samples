#include <iostream>
#include <gtest/gtest.h> // Google Test framework

// Custom allocator definition
template <typename T>
class CustomAllocator {
public:
    T* allocate(size_t size) {
        return new T[size];
    }

    void deallocate(T* ptr, size_t size) {
        delete[] ptr;
    }

    template<typename... Args>
    void construct(T* ptr, Args&&... args) {
        new (ptr) T(std::forward<Args>(args)...);
    }

    void destroy(T* ptr) {
        ptr->~T();
    }
};

class ComplexObject {
public:
    ComplexObject(int val, double factor) : value(val), multiplier(factor) {}
    double calculateResult() const { return value * multiplier; }

private:
    int value;
    double multiplier;
};

// Fixture class for common setup and teardown
class CustomAllocatorTest : public ::testing::Test {
protected:
    CustomAllocator<ComplexObject> myAllocator;

    void SetUp() override {
        // Additional setup code, if any
    }

    void TearDown() override {
        // Additional teardown code, if any
    }
};

TEST_F(CustomAllocatorTest, AllocatingAndInitializing) {
    ComplexObject* obj = myAllocator.allocate(1);

    ASSERT_NE(obj, nullptr);
    myAllocator.construct(obj, 5, 2.5);

    ASSERT_EQ(obj->calculateResult(), 12.5);

    myAllocator.destroy(obj);
    myAllocator.deallocate(obj, 1);
}

TEST_F(CustomAllocatorTest, AllocatingAndCopying) {
    ComplexObject* obj1 = myAllocator.allocate(1);
    ASSERT_NE(obj1, nullptr);
    myAllocator.construct(obj1, 5, 2.5);

    ComplexObject* obj2 = myAllocator.allocate(1);
    ASSERT_NE(obj2, nullptr);
    myAllocator.construct(obj2, *obj1);

    ASSERT_EQ(obj2->calculateResult(), obj1->calculateResult());

    myAllocator.destroy(obj1);
    myAllocator.destroy(obj2);

    myAllocator.deallocate(obj1, 1);
    myAllocator.deallocate(obj2, 1);
}

TEST_F(CustomAllocatorTest, MemoryReuseWithDifferentTypes) {
    CustomAllocator<int> intAllocator;

    int* data = intAllocator.allocate(3);
    ASSERT_NE(data, nullptr);
    intAllocator.deallocate(data, 3);

    ComplexObject* obj = myAllocator.allocate(2);
    ASSERT_NE(obj, nullptr);
    myAllocator.deallocate(obj, 2);
}

TEST_F(CustomAlignmentTest, VerifyAlignmentAndOverhead) {
    const size_t dataSize = 1000; // Adjust based on your specific needs

    // Allocate memory for objects of various sizes
    char* data1 = myAllocator.allocate(dataSize);
    char* data2 = myAllocator.allocate(dataSize * 2);
    char* data3 = myAllocator.allocate(dataSize * 3);

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

    // Deallocate memory
    myAllocator.deallocate(data1, dataSize);
    myAllocator.deallocate(data2, dataSize * 2);
    myAllocator.deallocate(data3, dataSize * 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
