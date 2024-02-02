/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 *
 * Memory Allocation Strategy Unit Tests
 *
 * Memory allocation strategies in C++ determine how dynamic memory is allocated and deallocated.
 * This file contains unit tests for advanced C++ skills related to memory allocation strategies.
 *
 * Here are some use cases where you might want to use a custom allocator with std::vector:
 *
 * Specialized Memory Management:
 *
 * If you have specific requirements for memory management that are not efficiently handled by the
 * default allocator (std::allocator), a custom allocator can be designed to meet those requirements.
 *
 * Memory Pools or Arenas:
 *
 * Custom allocators can be used to implement memory pools or arenas. This is useful in scenarios
 * where you want to pre-allocate a large block of memory and then manage smaller allocations within that block.
 *
 * Performance Optimization:
 * Depending on the specific use case and requirements, a custom allocator might offer performance
 * improvements. For example, it could be tailored for a specific memory access pattern, alignment,
 * or allocation strategy
 *
 * Integration with External Systems:
 * If you need to interface with an external system or library that has its own memory management
 * scheme, a custom allocator can be designed to work seamlessly with that system
 *
 * Resource Tracking or Logging:
 * You can use a custom allocator to track memory usage, log allocation and deallocation events, or
 * perform custom actions when memory is allocated or deallocated
 *
 * Debugging and Profiling:
 * Custom allocators are valuable in debugging scenarios. You can implement additional checks,
 * logging, or profiling information in a custom allocator to aid in identifying memory-related issues.
 *
 */

#include <gtest/gtest.h>
#include <memory>
#include <memory_resource>
#include <vector>

namespace
{
    // Custom Allocator Example
    template <typename T>
    struct CustomAllocator
    {
        using value_type = T;

        T *allocate(std::size_t n)
        {
            std::cout << "Custom allocation for " << n << " objects\n";
            return static_cast<T *>(::operator new(n * sizeof(T)));
        }

        void deallocate(T *p, std::size_t n)
        {
            std::cout << "Custom deallocation for " << n << " objects\n";
            ::operator delete(p);
        }
    };

    /*
     * Test 1: `StdAllocatorSingleObject`
     *   - Allocates and deallocates a single integer using `std::allocator`.
     */
    TEST(MemoryAllocation, StdAllocatorSingleObject)
    {
        std::allocator<int> allocator;

        int *value = allocator.allocate(1);
        *value = 42;

        EXPECT_EQ(*value, 42);

        allocator.deallocate(value, 1);
    }

    /*
     * Test 2: `CustomAllocatorInVector`
     *   - Uses a custom allocator (`CustomAllocator`) with a `std::vector` to manage memory for integers.
     */
    TEST(MemoryAllocation, CustomAllocatorInVector)
    {
        std::vector<int, CustomAllocator<int>> customVector;

        customVector.push_back(1);
        customVector.push_back(2);
        customVector.push_back(3);

        ASSERT_EQ(customVector.size(), 3);
        EXPECT_EQ(customVector[0], 1);
        EXPECT_EQ(customVector[1], 2);
        EXPECT_EQ(customVector[2], 3);
    }

    /*
     * Test 3: `PolymorphicAllocator`
     *   - Allocates and deallocates a single integer using `std::pmr::polymorphic_allocator`, demonstrating polymorphic memory allocation.
     */
    TEST(MemoryAllocation, PolymorphicAllocator)
    {
        // Create a polymorphic allocator using the default memory resource
        std::pmr::polymorphic_allocator<int> polyAllocator(std::pmr::get_default_resource());

        // Allocate memory for an integer
        int *value = polyAllocator.allocate(1);

        // Construct the integer with a value
        polyAllocator.construct(value, 42);

        // Expect the value to be 42
        EXPECT_EQ(*value, 42);

        // Deallocate the memory
        polyAllocator.deallocate(value, 1);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}