#include <gtest/gtest.h>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

namespace
{
    // Test 1: Basic Mutex Usage
    TEST(MutexTest, BasicUsage)
    {
        std::mutex mutex;
        int sharedValue = 0;

        {
            std::lock_guard<std::mutex> lock(mutex);
            sharedValue = 42;
        }

        ASSERT_EQ(sharedValue, 42);
    }

    // Test 2: Mutex with Multiple Threads
    TEST(MutexTest, MultipleThreads)
    {
        std::mutex mutex;
        int sharedValue = 0;

        std::thread t1([&mutex, &sharedValue]
                       {
        std::lock_guard<std::mutex> lock(mutex);
        sharedValue = 10; });

        t1.join(); // Ensure t1 completes before t2 is started
        std::thread t2([&mutex, &sharedValue]
                       {
        std::lock_guard<std::mutex> lock(mutex);
        sharedValue += 5; });

        t2.join();

        ASSERT_EQ(sharedValue, 15);
    }

    // Test 3: Deadlock Avoidance with Separate Locks
    // This test demonstrates the use of separate locks for distinct shared
    // resources to avoid contention and potential deadlocks.
    TEST(MutexTest, DeadlockAvoidance_SeparateLocks)
    {
        std::mutex mutex1, mutex2;
        int sharedValue1 = 0, sharedValue2 = 0;

        // Acquiring lock1 for sharedValue1
        {
            std::lock_guard<std::mutex> lock1(mutex1);
            sharedValue1 = 100; // Modify sharedValue1

            // Acquiring lock2 for sharedValue2 within the lock1-protected block
            {
                std::lock_guard<std::mutex> lock2(mutex2);
                sharedValue2 = 200; // Modify sharedValue2
            }
        }

        ASSERT_EQ(sharedValue1, 100);
        ASSERT_EQ(sharedValue2, 200);
    }

    // Test 4: Condition Variables with Mutex
    TEST(MutexTest, ConditionVariable)
    {
        std::mutex mutex;
        std::condition_variable cv;
        int sharedValue = 0;
        bool valueUpdated = false;

        std::thread t1([&mutex, &cv, &sharedValue, &valueUpdated]
                       {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [&valueUpdated] { return valueUpdated; });

        sharedValue *= 2; });

        {
            std::lock_guard<std::mutex> lock(mutex);
            sharedValue = 5;
            valueUpdated = true;
            cv.notify_one();
        }

        t1.join();

        ASSERT_EQ(sharedValue, 10);
    }

    class SharedResource
    {
    public:
        void modifySharedValue(int valueToAdd)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            sharedValue += valueToAdd;
        }

        int getSharedValue() const
        {
            std::lock_guard<std::mutex> lock(mutex_);
            return sharedValue;
        }

    private:
        mutable std::mutex mutex_;
        int sharedValue = 0;
    };

    // Test: Concurrent Modification of Shared Resource with Loop
    TEST(MutexTest, ConcurrentModificationWithLoop)
    {
        SharedResource sharedResource;

        const int expectedValue = 200; // 20 increments by each thread, 10 times

        std::thread t1([&sharedResource]
                       {
        for (int i = 0; i < 10; ++i) {
            // Each thread increments the shared value by 10, 10 times
            sharedResource.modifySharedValue(10);
        } });

        std::thread t2([&sharedResource]
                       {
        for (int i = 0; i < 10; ++i) {
            // Each thread increments the shared value by 10, 10 times
            sharedResource.modifySharedValue(10);
        } });

        t1.join();
        t2.join();

        // Check if the final value of the shared resource matches the expected value
        ASSERT_EQ(sharedResource.getSharedValue(), expectedValue);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
