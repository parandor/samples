/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <gtest/gtest.h>
#include <fstream>
#include <memory>

// Resource Acquisition Is Initialization (RAII) is a C++ programming idiom
// that ties the lifecycle of a resource (like memory, file handles, or network connections)
// to the scope of an object. The basic idea is to use the constructor of an object to
// acquire a resource and use the destructor to release it.

// Resource Acquisition:
//
// The process of obtaining or allocating a resource, such as opening a file, allocating memory,
// or establishing a network connection.
// This is typically done in the constructor of a class or object.
//
// Is Initialization:
//
// The act of initializing an object during its creation.
// In the context of RAII, resource acquisition is naturally tied to the initialization of an object.
//
// Lifecycle Management:
//
// The resource's lifecycle is managed by the object's lifecycle. When the object goes out of scope or
// is explicitly deleted, its destructor is called, and that's where resource cleanup occurs.
//
// Automatic Cleanup:
//
// RAII ensures that resources are automatically released when the object containing them goes out of scope.
// This automatic cleanup helps prevent resource leaks.

namespace
{
    // Resource Management Class for File Handling
    class FileHandler
    {
    public:
        explicit FileHandler(const std::string &filename)
            : filename(filename)
        {
            // Create the file during construction
            file.open(filename, std::ios::out | std::ios::app);
            if (!file.is_open())
            {
                throw std::runtime_error("Failed to open file");
            }
        }

        ~FileHandler()
        {
            // Automatically close the file during destruction
            if (file.is_open())
            {
                file.close();
            }

            // Delete the file during destruction if it exists
            if (std::ifstream(filename))
            {
                std::remove(filename.c_str());
            }
        }

        // Example method for writing a line to the file
        void writeLine(const std::string &content)
        {
            std::ofstream outputFile(filename, std::ios::app);
            if (!outputFile.is_open())
            {
                throw std::runtime_error("Failed to open or create file for writing");
            }
            outputFile << content << '\n';
        }

        // Example method for reading a line from the file
        std::string readLine()
        {
            std::string line;
            std::getline(file, line);
            return line;
        }

    private:
        std::string filename;
        std::ifstream file;
    };

    // Resource Management Class for Dynamic Memory
    class DynamicMemoryManager
    {
    public:
        explicit DynamicMemoryManager(size_t size)
            : data(new int[size]), size(size)
        {
            // Initialization logic, e.g., allocate dynamic memory
        }

        ~DynamicMemoryManager()
        {
            // Cleanup logic, e.g., deallocate dynamic memory
            delete[] data;
        }

        // Example method to get the size of the dynamic array
        size_t getSize() const
        {
            return size;
        }

    private:
        int *data;
        size_t size;
    };

    // Resource Management Class for Custom Resource
    class CustomResourceManager
    {
    public:
        explicit CustomResourceManager()
        {
            // Acquire custom resource, e.g., open a network connection
            // For the sake of the example, let's simulate acquiring a resource
            resourceAcquired = true;
        }

        ~CustomResourceManager()
        {
            // Release custom resource, e.g., close the network connection
            // For the sake of the example, let's simulate releasing a resource
            resourceAcquired = false;
        }

        // Example method to check if the resource is acquired
        bool isResourceAcquired() const
        {
            return resourceAcquired;
        }

    private:
        bool resourceAcquired;
    };

    // Unit test for FileHandler
    TEST(RAIITest, FileHandlerTest)
    {
        const std::string testFilename = "test.txt";

        // Use a block to ensure the FileHandler object is destroyed before expectations are checked
        try
        {
            // Creating FileHandler will create or open the file "test.txt"
            FileHandler fileHandler(testFilename);

            // Write a line to the file
            fileHandler.writeLine("Hello, RAII!");

            // Access the file resource using RAII
            std::string content = fileHandler.readLine();
            EXPECT_TRUE(content == "Hello, RAII!");
        }
        catch (const std::exception &e)
        {
            // Handle exceptions if needed
            ADD_FAILURE() << "Exception caught: " << e.what();
        }

        // Additional checks if needed after the FileHandler is destroyed
        EXPECT_FALSE(std::ifstream(testFilename).is_open()); // Check that the file is deleted
    }

    // Unit test for DynamicMemoryManager
    TEST(RAIITest, DynamicMemoryManagerTest)
    {
        EXPECT_NO_THROW({
            DynamicMemoryManager memoryManager(5);
            // Access the dynamic memory resource using RAII
            size_t size = memoryManager.getSize();
            EXPECT_EQ(size, 5);
        });
    }

    // Unit test for CustomResourceManager
    TEST(RAIITest, CustomResourceManagerTest)
    {
        EXPECT_NO_THROW({
            CustomResourceManager resourceManager;
            // Access the custom resource using RAII
            bool resourceAcquired = resourceManager.isResourceAcquired();
            EXPECT_TRUE(resourceAcquired);
        });
    }
}

// Main function for running the tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
