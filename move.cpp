/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <vector>

class MyResource
{
public:
    MyResource(int value) : data(value)
    {
        std::cout << "Resource acquired! Value: " << data << std::endl;
    }

    ~MyResource()
    {
        std::cout << "Resource released! Value: " << data << std::endl;
    }

    int getData() const
    {
        return data;
    }

private:
    int data;
};

class ResourceManager
{
public:
    // Default constructor
    ResourceManager() = default;

    // Add a resource to the manager
    void addResource(std::unique_ptr<MyResource> resource)
    {
        resources.push_back(std::move(resource));
    }

    // Move constructor
    ResourceManager(ResourceManager &&other) noexcept : resources(std::move(other.resources))
    {
        std::cout << "ResourceManager Move Constructor called." << std::endl;
    }

    // Move assignment operator
    ResourceManager &operator=(ResourceManager &&other) noexcept
    {
        // Ensures that the assignment is not being done to the same object, preventing self-assignment
        if (this != &other)
        {
            resources = std::move(other.resources);
            std::cout << "ResourceManager Move Assignment Operator called." << std::endl;
        }
        return *this;
    }

    // Display the values of resources
    void displayResources() const
    {
        std::cout << "ResourceManager Contents:" << std::endl;
        for (const auto &resource : resources)
        {
            std::cout << resource->getData() << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::unique_ptr<MyResource>> resources;
};

TEST(SharedPtrMoveTest, MoveSharedResource)
{
    std::shared_ptr<MyResource> sharedPtr1 = std::make_shared<MyResource>(42);

    // Move shared_ptr ownership using std::move()
    std::shared_ptr<MyResource> sharedPtr2 = std::move(sharedPtr1);

    EXPECT_EQ(sharedPtr1, nullptr); // sharedPtr1 should be null after the move
    EXPECT_NE(sharedPtr2, nullptr); // sharedPtr2 should be valid after the move

    // Access the resource through sharedPtr2
    EXPECT_EQ(sharedPtr2->getData(), 42);
}

TEST(UniquePtrMoveTest, MoveUniqueResource)
{
    std::unique_ptr<MyResource> uniquePtr1 = std::make_unique<MyResource>(99);

    // Move unique_ptr ownership using std::move()
    std::unique_ptr<MyResource> uniquePtr2 = std::move(uniquePtr1);

    EXPECT_EQ(uniquePtr1, nullptr); // uniquePtr1 should be null after the move
    EXPECT_NE(uniquePtr2, nullptr); // uniquePtr2 should be valid after the move

    // Access the resource through uniquePtr2
    EXPECT_EQ(uniquePtr2->getData(), 99);
}

TEST(UniquePtrResetTest, MoveAndResetUniqueResource)
{
    std::unique_ptr<MyResource> uniquePtr1 = std::make_unique<MyResource>(123);

    // Move unique_ptr ownership using std::move()
    std::unique_ptr<MyResource> uniquePtr2 = std::move(uniquePtr1);

    EXPECT_EQ(uniquePtr1, nullptr); // uniquePtr1 should be null after the move
    EXPECT_NE(uniquePtr2, nullptr); // uniquePtr2 should be valid after the move

    // Access the resource through uniquePtr2
    EXPECT_EQ(uniquePtr2->getData(), 123);

    // Reset uniquePtr2, releasing the resource
    uniquePtr2.reset();

    EXPECT_EQ(uniquePtr2, nullptr); // uniquePtr2 should be null after the reset
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // Create a ResourceManager and add resources to it
    ResourceManager manager1;
    manager1.addResource(std::make_unique<MyResource>(42));
    manager1.addResource(std::make_unique<MyResource>(77));

    // Display the contents of manager1
    std::cout << "Before Move:" << std::endl;
    manager1.displayResources();

    // Move construct a new ResourceManager using std::move()
    ResourceManager manager2 = std::move(manager1);

    // Display the contents of manager1 after the move (should be empty)
    std::cout << "After Move:" << std::endl;
    manager1.displayResources();

    // Display the contents of manager2 after the move (should contain the resources)
    manager2.displayResources();

    return RUN_ALL_TESTS();
}
