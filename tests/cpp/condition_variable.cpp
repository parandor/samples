#include <gtest/gtest.h>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

namespace
{
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

    // Test 1: Basic Condition Variable Usage
    TEST(ConditionVariableTest, BasicUsage)
    {
        std::mutex mutex;
        std::condition_variable cv;
        bool flag = false;

        std::thread t1([&mutex, &cv, &flag]
                       {
        std::unique_lock<std::mutex> lock(mutex);
        flag = true;
        cv.notify_one(); });

        int number = 0;
        std::thread t2([&mutex, &cv, &flag, &number]
                       {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [&flag] { return flag; });
        // Do something after the flag is set
        number = 10; });

        t1.join();
        t2.join();

        ASSERT_TRUE(flag);
        ASSERT_EQ(number, 10);
    }

    // Test 2: Producer-Consumer with Condition Variable
    TEST(ConditionVariableTest, ProducerConsumer)
    {
        std::mutex mutex;
        std::condition_variable cv;
        int sharedValue = 0;
        bool dataReady = false;

        std::thread producer([&mutex, &cv, &sharedValue, &dataReady]
                             {
        std::lock_guard<std::mutex> lock(mutex);
        sharedValue = 42;
        dataReady = true;
        cv.notify_one(); });

        std::thread consumer([&mutex, &cv, &sharedValue, &dataReady]
                             {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [&dataReady] { return dataReady; });
        // Consume the shared value
        int result = sharedValue * 2;
        ASSERT_EQ(result, 84); });

        producer.join();
        consumer.join();

        ASSERT_EQ(sharedValue, 42);
        ASSERT_TRUE(dataReady);
    }

    // Test 3: Timed Waiting with Condition Variable
    TEST(ConditionVariableTest, TimedWaiting)
    {
        std::mutex mutex;
        std::condition_variable cv;
        bool flag = false;

        std::thread t1([&mutex, &cv, &flag]
                       {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        {
            std::lock_guard<std::mutex> lock(mutex);
            flag = true;
            cv.notify_one();
        } });

        std::thread t2([&mutex, &cv, &flag]
                       {
        std::unique_lock<std::mutex> lock(mutex);
        if (cv.wait_for(lock, std::chrono::milliseconds(1000), [&flag] { return flag; })) {
            // Do something after the flag is set
        } else {
            // Handle timeout
            FAIL() << "Timeout occurred";
        } });

        t1.join();
        t2.join();

        ASSERT_TRUE(flag);
    }

    // Test 4: Multiple Conditions with Condition Variable
    TEST(ConditionVariableTest, MultipleConditions)
    {
        std::mutex mutex;
        std::condition_variable cv1, cv2;
        bool condition1 = false;
        bool condition2 = false;

        std::thread t1([&mutex, &cv1, &condition1]
                       {
        std::unique_lock<std::mutex> lock(mutex);
        condition1 = true;
        cv1.notify_one(); });

        std::thread t2([&mutex, &cv1, &cv2, &condition1, &condition2]
                       {
        std::unique_lock<std::mutex> lock(mutex);
        cv1.wait(lock, [&condition1] { return condition1; });
        condition2 = true;
        cv2.notify_one(); });

        t1.join();
        t2.join();

        ASSERT_TRUE(condition1);
        ASSERT_TRUE(condition2);
    }

    // Test 5: Producer-Consumer with Bounded Buffer
    TEST(ConditionVariableTest, BoundedBuffer)
    {
        std::mutex mtx;
        std::condition_variable notFull, notEmpty;
        std::vector<int> buffer;
        const int bufferSize = 50;
        const int numPackets = 1000;

        std::thread consumer([&]
                             {
        for (int i = 0; i < numPackets; ++i) {
            std::unique_lock<std::mutex> lock(mtx);
            notEmpty.wait(lock, [&] { return buffer.size() == bufferSize; });
            for(int j = 0; j<bufferSize; ++j) {
                // Consume data from the buffer
                int data = buffer.back();
                ASSERT_EQ(data, i);
                buffer.pop_back();
            }
            lock.unlock();
            notFull.notify_one();  // Move notify_one here
        } });

        std::thread producer([&]
                             {
        for (int i = 0; i < numPackets; ++i) {
            std::unique_lock<std::mutex> lock(mtx);
            notFull.wait(lock, [&] { return buffer.size() < bufferSize; });
            for(int j = 0; j<bufferSize; ++j) {
                // Produce data and add to the buffer
                buffer.push_back(i);
            }
            lock.unlock();
            notEmpty.notify_one();
        } });

        producer.join();
        consumer.join();

        ASSERT_TRUE(buffer.empty());
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
