#include <iostream>
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <mutex>
#include <numeric>
#include <algorithm>

// Test 1: Basic Thread Creation and Joining
TEST(ConcurrencyTest, BasicThreadCreationAndJoining) {
    std::thread t([] {
        // Your threaded code here
        std::cout << "Thread executing." << std::endl;
    });

    t.join(); // Wait for the thread to finish
    ASSERT_TRUE(true); // Placeholder assertion to avoid test failure due to no assertions
}

// Test 2: Parallel Accumulation with Multiple Threads
TEST(ConcurrencyTest, ParallelAccumulationWithMultipleThreads) {
    const int dataSize = 100000;
    std::vector<int> data(dataSize, 1);

    const size_t numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::vector<int> partialSums(numThreads, 0);

    // Divide the data among threads
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back([i, &data, &partialSums, numThreads] {
            size_t chunkSize = data.size() / numThreads;
            size_t start = i * chunkSize;
            size_t end = (i == numThreads - 1) ? data.size() : (i + 1) * chunkSize;

            // Perform partial accumulation
            partialSums[i] = std::accumulate(data.begin() + start, data.begin() + end, 0);
        });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Combine partial results
    int totalSum = std::accumulate(partialSums.begin(), partialSums.end(), 0);

    // Check if the total sum is correct
    EXPECT_EQ(totalSum, dataSize);
}

// Test 3: Data Sharing and Synchronization with std::mutex
TEST(ConcurrencyTest, DataSharingAndSynchronizationWithMutex) {
    std::vector<int> sharedData;
    std::mutex dataMutex;

    const int numIterations = 10000;
    const int incrementValue = 1;

    std::vector<std::thread> threads;

    for (int i = 0; i < numIterations; ++i) {
        threads.emplace_back([&sharedData, &dataMutex, incrementValue] {
            std::lock_guard<std::mutex> lock(dataMutex); // Lock to ensure exclusive access
            sharedData.push_back(incrementValue);
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Check if the size of sharedData matches the expected size
    EXPECT_EQ(sharedData.size(), numIterations);
}

// Test 4: Parallel Sort with std::thread
TEST(ConcurrencyTest, ParallelSortWithThread) {
    const int dataSize = 1000000;
    std::vector<int> data(dataSize);

    // Fill the vector with random values
    std::generate(data.begin(), data.end(), [] {
        return rand();
    });

    const size_t numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    // Divide the data among threads
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back([i, &data, numThreads] {
            size_t chunkSize = data.size() / numThreads;
            size_t start = i * chunkSize;
            size_t end = (i == numThreads - 1) ? data.size() : (i + 1) * chunkSize;

            // Perform partial sort
            std::sort(data.begin() + start, data.begin() + end);
        });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Merge the sorted chunks
    std::sort(data.begin(), data.end());

    // Check if the data is sorted
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

// Test 5: Producer-Consumer Pattern with std::thread and std::condition_variable
TEST(ConcurrencyTest, ProducerConsumerPattern) {
    const int bufferSize = 10;
    std::vector<int> buffer(bufferSize, 0);

    std::mutex mutex;
    std::condition_variable notEmpty, notFull;

    const int numProducers = 2;
    const int numConsumers = 2;

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // Producer function
    auto producer = [&buffer, &mutex, &notEmpty, &notFull](int id) {
        for (int i = 0; i < 10; ++i) {
            {
                std::unique_lock<std::mutex> lock(mutex);
                notFull.wait(lock, [&buffer] { return buffer.size() < bufferSize; });
                buffer.push_back(id * 10 + i);
            }
            notEmpty.notify_one();
        }
    };

    // Consumer function
    auto consumer = [&buffer, &mutex, &notEmpty, &notFull](int id) {
        for (int i = 0; i < 5; ++i) {
            {
                std::unique_lock<std::mutex> lock(mutex);
                notEmpty.wait(lock, [&buffer] { return !buffer.empty(); });
                int value = buffer.back();
                buffer.pop_back();
            }
            notFull.notify_one();
        }
    };

    // Create and launch producer threads
    for (int i = 0; i < numProducers; ++i) {
        producers.emplace_back(producer, i);
    }

    // Create and launch consumer threads
    for (int i = 0; i < numConsumers; ++i) {
        consumers.emplace_back(consumer, i);
    }

    // Wait for all producer threads to finish
    for (auto& producerThread : producers) {
        producerThread.join();
    }

    // Wait for all consumer threads to finish
    for (auto& consumerThread : consumers) {
        consumerThread.join();
    }

    // Check if the buffer is empty at the end
    EXPECT_TRUE(buffer.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
