/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <iostream>
#include <gtest/gtest.h>

template <typename T>
class CustomAllocator {
public:
    CustomAllocator() : allocationCount(0), deallocationCount(0) {}

    T* allocate(size_t size) {
        T* ptr = new T[size];
        allocationCount++;
        return ptr;
    }

    void deallocate(T* ptr, size_t size) {
        delete[] ptr;
        deallocationCount++;
    }

    // Basic memory leak detection
    bool detectMemoryLeaks() const {
        return allocationCount != deallocationCount;
    }

    // Custom memory leak detection (replace with your actual detection logic)
    bool customMemoryLeakDetection(T* ptr, size_t size) const {
        // In this example, checks if all allocations have been deallocated
        return allocationCount != deallocationCount || allocationCount == 0;
    }

private:
    size_t allocationCount;
    size_t deallocationCount;
};

class MemoryLeakDetectionTest : public ::testing::Test {
protected:
    CustomAllocator<int> myAllocator;

    void SetUp() override {
        // Additional setup code, if any
    }

    void TearDown() override {
        // Additional teardown code, if any
    }
};

// Test 1: Intentional Memory Leak
TEST_F(MemoryLeakDetectionTest, IntentionalMemoryLeak) {
    int* data = myAllocator.allocate(10);
    // Do not deallocate data intentionally to create a memory leak

    EXPECT_TRUE(myAllocator.detectMemoryLeaks());
}

// Test 2: Detect Memory Leak After Deallocation
TEST_F(MemoryLeakDetectionTest, DetectMemoryLeakAfterDeallocation) {
    int* data = myAllocator.allocate(5);
    myAllocator.deallocate(data, 5);

    EXPECT_FALSE(myAllocator.detectMemoryLeaks());
}

// Test 3: Intentional Memory Leak with Custom Detection
TEST_F(MemoryLeakDetectionTest, IntentionalMemoryLeakWithCustomDetection) {
    int* data = myAllocator.allocate(7);
    // Do not deallocate data intentionally to create a memory leak

    EXPECT_TRUE(myAllocator.customMemoryLeakDetection(data, 7));
}

// Test 4: Detect Memory Leak After Intentional Memory Leak and Deallocation
TEST_F(MemoryLeakDetectionTest, DetectMemoryLeakAfterIntentionalLeakAndDeallocation) {
    int* data = myAllocator.allocate(3);
    // Do not deallocate data intentionally to create a memory leak

    EXPECT_TRUE(myAllocator.customMemoryLeakDetection(data, 3));

    myAllocator.deallocate(data, 3);

    EXPECT_FALSE(myAllocator.detectMemoryLeaks());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
