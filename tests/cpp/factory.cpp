// Comments explaining Factory Design Pattern

// The Factory design pattern is a creational pattern that provides an interface
// for creating objects in a super class, but allows subclasses to alter the type
// of objects that will be created. It promotes loose coupling by eliminating the
// need to bind application-specific classes into the code.

// Use Cases:

// 1. **Object Creation Variability:**
//    When the system needs to be independent of how its objects are created,
//    composed, and represented, and the classes to instantiate are specified
//    at runtime.

// 2. **Class Hierarchy Usage:**
//    When the system is configured with multiple families of objects and needs
//    to ensure the compatibility of objects created in its subclasses.

// 3. **Encapsulation of Object Creation:**
//    When the responsibility of object creation and its representation details
//    should be encapsulated in a separate class or component.

// 4. **Dynamic Switching:**
//    When there's a need for dynamic runtime switching of the types of objects
//    to be created, facilitating easy adaptability and configuration changes.

#include <gtest/gtest.h>
#include <memory>

// Product interface
class Product {
public:
    virtual ~Product() = default;
    virtual std::string getName() const = 0;
    virtual int getPrice() const = 0;
};

// Concrete Product A
class ConcreteProductA : public Product {
public:
    std::string getName() const override { return "Product A"; }
    int getPrice() const override { return 100; }
};

// Concrete Product B
class ConcreteProductB : public Product {
public:
    std::string getName() const override { return "Product B"; }
    int getPrice() const override { return 150; }
};

// Factory interface
class Factory {
public:
    virtual std::unique_ptr<Product> createProduct() const = 0;
};

// Concrete Factory A
class ConcreteFactoryA : public Factory {
public:
    std::unique_ptr<Product> createProduct() const override {
        return std::make_unique<ConcreteProductA>();
    }
};

// Concrete Factory B
class ConcreteFactoryB : public Factory {
public:
    std::unique_ptr<Product> createProduct() const override {
        return std::make_unique<ConcreteProductB>();
    }
};

// GUnit Tests

// Test Factory A with Product A
TEST(FactoryPatternTests, FactoryAProductATest) {
    ConcreteFactoryA factoryA;
    auto product = factoryA.createProduct();
    ASSERT_EQ(product->getName(), "Product A");
    ASSERT_EQ(product->getPrice(), 100);
}

// Test Factory B with Product B
TEST(FactoryPatternTests, FactoryBProductBTest) {
    ConcreteFactoryB factoryB;
    auto product = factoryB.createProduct();
    ASSERT_EQ(product->getName(), "Product B");
    ASSERT_EQ(product->getPrice(), 150);
}

// Test Factory A with Product B (using polymorphism)
TEST(FactoryPatternTests, FactoryAProductBTest) {
    std::unique_ptr<Factory> factory = std::make_unique<ConcreteFactoryA>();
    auto product = factory->createProduct();
    ASSERT_EQ(product->getName(), "Product A");
    ASSERT_EQ(product->getPrice(), 100);
}

// Test Factory B with Product A (using polymorphism)
TEST(FactoryPatternTests, FactoryBProductATest) {
    std::unique_ptr<Factory> factory = std::make_unique<ConcreteFactoryB>();
    auto product = factory->createProduct();
    ASSERT_EQ(product->getName(), "Product B");
    ASSERT_EQ(product->getPrice(), 150);
}

// Test dynamic switching of factories
TEST(FactoryPatternTests, DynamicFactorySwitchTest) {
    std::unique_ptr<Factory> factory;
    
    factory = std::make_unique<ConcreteFactoryA>();
    auto productA = factory->createProduct();
    ASSERT_EQ(productA->getName(), "Product A");
    
    factory = std::make_unique<ConcreteFactoryB>();
    auto productB = factory->createProduct();
    ASSERT_EQ(productB->getName(), "Product B");
}
