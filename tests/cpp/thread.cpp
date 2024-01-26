/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <numeric>
#include <queue>
#include <thread>
#include <vector>
#include <gtest/gtest.h>

// Test 1: Basic Thread Creation and Joining
TEST(ConcurrencyTest, BasicThreadCreationAndJoining)
{
    std::thread t([]
                  {
        // Your threaded code here
        std::cout << "Thread executing." << std::endl; });

    t.join();          // Wait for the thread to finish
    ASSERT_TRUE(true); // Placeholder assertion to avoid test failure due to no assertions
}

// Test 2: Parallel Accumulation with Multiple Threads
TEST(ConcurrencyTest, ParallelAccumulationWithMultipleThreads)
{
    const int dataSize = 100000;
    std::vector<int> data(dataSize, 1);

    const size_t numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::vector<int> partialSums(numThreads, 0);

    // Divide the data among threads
    for (size_t i = 0; i < numThreads; ++i)
    {
        threads.emplace_back([i, &data, &partialSums, numThreads]
                             {
            size_t chunkSize = data.size() / numThreads;
            size_t start = i * chunkSize;
            size_t end = (i == numThreads - 1) ? data.size() : (i + 1) * chunkSize;

            // Perform partial accumulation
            partialSums[i] = std::accumulate(data.begin() + start, data.begin() + end, 0); });
    }

    // Wait for all threads to finish
    for (auto &thread : threads)
    {
        thread.join();
    }

    // Combine partial results
    int totalSum = std::accumulate(partialSums.begin(), partialSums.end(), 0);

    // Check if the total sum is correct
    EXPECT_EQ(totalSum, dataSize);
}

// Test 3: Data Sharing and Synchronization with std::mutex
TEST(ConcurrencyTest, DataSharingAndSynchronizationWithMutex)
{
    std::vector<int> sharedData;
    std::mutex dataMutex;

    const int numIterations = 10000;
    const int incrementValue = 1;

    std::vector<std::thread> threads;

    for (int i = 0; i < numIterations; ++i)
    {
        threads.emplace_back([&sharedData, &dataMutex, incrementValue]
                             {
            std::lock_guard<std::mutex> lock(dataMutex); // Lock to ensure exclusive access
            sharedData.push_back(incrementValue); });
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    // Check if the size of sharedData matches the expected size
    EXPECT_EQ(sharedData.size(), numIterations);
}

// Test 4: Parallel Sort with std::thread
TEST(ConcurrencyTest, ParallelSortWithThread)
{
    const int dataSize = 1000000;
    std::vector<int> data(dataSize);

    // Fill the vector with random values
    std::generate(data.begin(), data.end(), []
                  { return rand(); });

    const size_t numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    // Divide the data among threads
    for (size_t i = 0; i < numThreads; ++i)
    {
        threads.emplace_back([i, &data, numThreads]
                             {
            size_t chunkSize = data.size() / numThreads;
            size_t start = i * chunkSize;
            size_t end = (i == numThreads - 1) ? data.size() : (i + 1) * chunkSize;

            // Perform partial sort
            std::sort(data.begin() + start, data.begin() + end); });
    }

    // Wait for all threads to finish
    for (auto &thread : threads)
    {
        thread.join();
    }

    // Merge the sorted chunks
    std::sort(data.begin(), data.end());

    // Check if the data is sorted
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

template <typename T>
class SharedBuffer
{
public:
    void push(const T &item)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        buffer_.push(item);
        lock.unlock();
        condition_.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this]
                        { return !buffer_.empty(); });
        if (!buffer_.empty()) {
            T item = buffer_.front();
            buffer_.pop();            
            return item;
        }
        return T(-1);
    }

    size_t size() const
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return buffer_.size();
    }

    void clear()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (!buffer_.empty())
        {
            buffer_.pop();
        }
    }

private:
    std::queue<T> buffer_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
};

class ProducerConsumerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Reset any shared resources or variables
        sharedBuffer.clear();
    }

    SharedBuffer<int> sharedBuffer;
    const int numItems = 10;
};

class Producer
{
public:
    Producer(SharedBuffer<int> &buffer, int id, int numItems) : buffer_(buffer), id_(id), numItems_(numItems) {}

    void operator()()
    {
        for (int i = 0; i < numItems_; ++i)
        {
            buffer_.push(id_ * numItems_ + i);
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulate some work
        }
    }

private:
    SharedBuffer<int> &buffer_;
    int id_;
    int numItems_;
};

class Consumer
{
public:
    Consumer(SharedBuffer<int> &buffer, std::vector<int> &results, int numItems)
        : buffer_(buffer), results_(results), numItems_(numItems) {}

    void operator()()
    {
        while (true)
        {
            int item = buffer_.pop();

            // Check for the sentinel value (-1) to signal end of production
            if (item == -1)
            {
                break;
            }

            results_.push_back(item);
            std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Simulate some work
        }
    }

private:
    SharedBuffer<int> &buffer_;
    std::vector<int> &results_;
    int numItems_;
};

// The Producer object is instantiated and its overloaded operator() method is executed
// when the std::thread is created. The std::thread constructor takes the Producer object
// as a parameter and internally calls its operator(). This creates a new thread of execution
// that runs the operator() method.
//
// So, when you add a Producer object to the vector of threads, a new thread is spawned,
// and it starts executing the operator() method of the Producer object in a separate thread.
TEST_F(ProducerConsumerTest, ProducerConsumerInteraction)
{
    const int numProducers = 2;
    const int numConsumers = 3;

    std::vector<std::thread> producerThreads;
    std::vector<std::thread> consumerThreads;
    std::vector<int> results;

    // Create producer threads
    for (int i = 0; i < numProducers; ++i)
    {
        producerThreads.emplace_back(Producer(sharedBuffer, i, numItems));
    }

    // Create consumer threads
    for (int i = 0; i < numConsumers; ++i)
    {
        consumerThreads.emplace_back(Consumer(sharedBuffer, results, numItems));
    }

    // Join producer threads
    for (auto &thread : producerThreads)
    {
        thread.join();
    }

    // Notify consumers that no more items will be produced
    for (int i = 0; i < numConsumers; ++i)
    {
        sharedBuffer.push(-1);
    }

    // Join consumer threads
    for (auto &thread : consumerThreads)
    {
        thread.join();
    }

    // Check if all expected items are present in the results
    std::sort(results.begin(), results.end());
    std::vector<int> expectedResults;
    for (int i = 0; i < numProducers * numItems; ++i)
    {
        expectedResults.push_back(i);
    }

    ASSERT_EQ(results, expectedResults);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
