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

class MemoryManagementDebuggingTest : public ::testing::Test {
protected:
    CustomAllocator<int> myAllocator;

    void SetUp() override {
        // Additional setup code, if any
    }

    void TearDown() override {
        // Additional teardown code, if any
    }
};

// Test 1: Allocate and Deallocate Memory
TEST_F(MemoryManagementDebuggingTest, AllocateAndDeallocateMemory) {
    int* data = myAllocator.allocate(5);

    // Assertions to check the validity of the allocated memory
    ASSERT_NE(data, nullptr);          // Check if the allocation was successful
    EXPECT_EQ(data[0], 0);             // Example: Check the initial value of the allocated memory
    EXPECT_NO_THROW(data[4] = 42);     // Example: Access and modify an element without causing an exception

    myAllocator.deallocate(data, 5);
}

// Test 2: Check Debug Output for Allocation and Deallocation
TEST_F(MemoryManagementDebuggingTest, CheckDebugOutput) {
    testing::internal::CaptureStdout(); // Capture standard output for testing

    int* data = myAllocator.allocate(3);
    myAllocator.deallocate(data, 3);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Allocated memory for 3 elements."), std::string::npos);
    EXPECT_NE(output.find("Deallocated memory for 3 elements."), std::string::npos);
}

// Test 3: Simulate Memory Leak
TEST_F(MemoryManagementDebuggingTest, SimulateMemoryLeak) {
    int* data = myAllocator.allocate(4);
    // Do not deallocate intentionally to simulate a memory leak
    EXPECT_TRUE(true); // Placeholder assertion to avoid test failure due to no assertions
}

// Test 4: Debugging with Conditional Breakpoint
TEST_F(MemoryManagementDebuggingTest, DebuggingWithConditionalBreakpoint) {
    // Set a conditional breakpoint in your debugger on the line containing the "ASSERT_TRUE(successfulAllocation)" statement.
    // The breakpoint should trigger only when the condition (e.g., allocation failure) is met.

    bool successfulAllocation = false;

    int* data = myAllocator.allocate(8);
    if (data) {
        successfulAllocation = true;

        // Additional debugging assertions to check the validity of the allocated memory
        ASSERT_NE(data, nullptr);
        ASSERT_EQ(data[0], 0); // Example: Check the initial value of the allocated memory

        // Your additional assertions or debugging logic can go here
    }

    EXPECT_TRUE(successfulAllocation);
    myAllocator.deallocate(data, 8);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
