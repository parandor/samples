#include <gtest/gtest.h>
#include <atomic>
#include <thread>

// Beginner level test: Simple atomic integer increment
TEST(AtomicTests, BeginnerIncrement) {
    std::atomic<int> counter(0);

    // Increment the atomic counter using multiple threads
    std::thread thread1([&counter]() {
        for (int i = 0; i < 10000; ++i) {
            counter++;
        }
    });

    std::thread thread2([&counter]() {
        for (int i = 0; i < 10000; ++i) {
            counter++;
        }
    });

    // Wait for threads to finish
    thread1.join();
    thread2.join();

    // Check if the counter value is as expected
    EXPECT_EQ(counter.load(), 20000);
}

// Advanced level test: Using atomic_flag as a spin lock
TEST(AtomicTests, SpinLock) {
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
    int sharedValue = 0;

    // Function to increment sharedValue with spin lock
    auto incrementWithLock = [&]() {
        while (lock.test_and_set(std::memory_order_acquire)) {
            // Spin until the lock is acquired
        }
        sharedValue++;
        lock.clear(std::memory_order_release);  // Release the lock
    };

    std::thread thread1(incrementWithLock);
    std::thread thread2(incrementWithLock);

    // Wait for threads to finish
    thread1.join();
    thread2.join();

    // Check if the sharedValue is as expected
    EXPECT_EQ(sharedValue, 2);
}

// Advanced level test: Atomic compare-and-swap (CAS) operation
TEST(AtomicTests, CASOperation) {
    std::atomic<int> value(10);

    // Try to update the value using CAS operation
    int expected = 10;
    int newValue = 20;

    // CAS loop
    while (!value.compare_exchange_weak(expected, newValue)) {
        // Retry if the value has changed since the last read
        expected = 10;
    }

    // Check if the value is updated successfully
    EXPECT_EQ(value.load(), 20);
}

// Advanced level test: Using atomic_flag to implement a simple spin lock
TEST(AtomicTests, SimpleSpinLock) {
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
    int criticalSection = 0;

    // Function to enter a critical section using spin lock
    auto enterCriticalSection = [&]() {
        while (lock.test_and_set(std::memory_order_acquire)) {
            // Spin until the lock is acquired
        }
        // Critical section
        criticalSection++;
        lock.clear(std::memory_order_release);  // Release the lock
    };

    std::thread thread1(enterCriticalSection);
    std::thread thread2(enterCriticalSection);

    // Wait for threads to finish
    thread1.join();
    thread2.join();

    // Check if the criticalSection is incremented correctly
    EXPECT_EQ(criticalSection, 2);
}

// Advanced level test: Using atomic operations for safe lazy initialization
TEST(AtomicTests, LazyInitialization) {
    std::atomic<int*> sharedPtr(nullptr);

    // Function for lazy initialization of a shared pointer
    auto lazyInitialize = [&]() {
        int* localPtr = new int(42);

        // Atomic compare-and-swap to update sharedPtr only if it's still nullptr
        int* expected = nullptr;
        if (sharedPtr.compare_exchange_strong(expected, localPtr)) {
            // Successfully initialized the shared pointer
        } else {
            // Another thread already initialized it, delete the local pointer
            delete localPtr;
        }
    };

    std::thread thread1(lazyInitialize);
    std::thread thread2(lazyInitialize);

    // Wait for threads to finish
    thread1.join();
    thread2.join();

    // Check if only one thread successfully initialized the shared pointer
    EXPECT_NE(sharedPtr.load(), nullptr);
}
