/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#include <memory>
#include <gtest/gtest.h>

class Resource
{
public:
    Resource()
    {
        std::cout << "Resource acquired." << std::endl;
    }

    ~Resource()
    {
        std::cout << "Resource released." << std::endl;
    }

    void performTask()
    {
        std::cout << "Task performed using the resource." << std::endl;
    }
};

class ComplexObject
{
public:
    std::string name;
    std::shared_ptr<Resource> resource;

    // Corrected constructor
    ComplexObject(const std::string &n, std::shared_ptr<Resource> res) : name(n), resource(std::move(res)) {}

    void execute()
    {
        std::cout << "Executing complex task with " << name << std::endl;
        resource->performTask();
    }
};

// Test case for std::shared_ptr with a complex object
TEST(SmartPointersTest, SharedPtrComplexObjectTest)
{
    // Creating a shared_ptr to a Resource
    auto sharedResource = std::make_shared<Resource>();

    // Creating a shared_ptr to a ComplexObject using the shared Resource
    std::shared_ptr<ComplexObject> sharedComplexObject = std::make_shared<ComplexObject>("Object1", sharedResource);

    // Accessing the ComplexObject and performing a task
    sharedComplexObject->execute();

    // Creating another shared_ptr pointing to the same ComplexObject
    std::shared_ptr<ComplexObject> sharedComplexObject2 = sharedComplexObject;

    // Modifying the ComplexObject through one shared_ptr should reflect in the other
    sharedComplexObject->name = "ModifiedObject";
    EXPECT_EQ(sharedComplexObject2->name, "ModifiedObject");
}

// Test case for std::unique_ptr with a dynamically allocated object
TEST(SmartPointersTest, UniquePtrDynamicObjectTest)
{
    // Creating a unique_ptr to a ComplexObject with a dynamically allocated Resource
    std::unique_ptr<ComplexObject> uniqueComplexObject = std::make_unique<ComplexObject>("Object2", std::make_shared<Resource>());

    // Accessing the ComplexObject and performing a task
    uniqueComplexObject->execute();

    // Moving ownership to another unique_ptr
    std::unique_ptr<ComplexObject> uniqueComplexObject2 = std::move(uniqueComplexObject);

    // uniqueComplexObject should be null after the move
    EXPECT_EQ(uniqueComplexObject, nullptr);

    // Modifying the ComplexObject through one unique_ptr
    uniqueComplexObject2->name = "ModifiedObject";
    EXPECT_EQ(uniqueComplexObject2->name, "ModifiedObject");
}

// Test case for std::weak_ptr with a cyclic reference between two objects
TEST(SmartPointersTest, WeakPtrCyclicReferenceTest)
{
    // Creating a shared_ptr and a weak_ptr with cyclic reference
    std::shared_ptr<ComplexObject> object1 = std::make_shared<ComplexObject>("Object3", nullptr);
    std::shared_ptr<ComplexObject> object2 = std::make_shared<ComplexObject>("Object4", nullptr);

    // Creating a cyclic reference
    object1->resource = std::make_shared<Resource>();
    object2->resource = object1->resource;

    object1->execute();
    object2->execute();

    // Breaking the cyclic reference by using weak_ptr
    std::weak_ptr<Resource> weakResource = object1->resource;
    object1->resource = nullptr;
    object2->resource = nullptr;

    // Checking if the weak_ptr is expired
    EXPECT_TRUE(weakResource.expired());

    // Accessing the Resource through the weak_ptr
    auto sharedResource = weakResource.lock();
    EXPECT_TRUE(sharedResource == nullptr);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    std::cout << "Hello world!" << std::endl;

    return RUN_ALL_TESTS();
}