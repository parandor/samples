// Comments explaining Strategy Design Pattern

// The Strategy design pattern is a behavioral pattern that defines a family
// of algorithms, encapsulates each algorithm, and makes them interchangeable.
// It lets the client choose the appropriate algorithm at runtime.

// Use Cases:

// 1. **Algorithm Variations:**
//    When you have multiple algorithms that can be used interchangeably, and
//    you want to make the system flexible and easily extensible.

// 2. **Avoiding Conditional Statements:**
//    When you want to avoid using conditional statements to select an algorithm
//    at runtime, making the code more maintainable and extensible.

// 3. **Algorithm Selection Dynamically:**
//    When you want to allow clients to choose algorithms at runtime based on
//    specific requirements or preferences.

#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Strategy interface
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void execute(int& variable1, int& variable2) const = 0;
};

// Concrete Strategies

// Concrete Strategy A - Simple Increment
class ConcreteStrategyA : public Strategy {
public:
    void execute(int& variable1, int& variable2) const override {
        // Simple increment strategy
        ++variable1;
        ++variable2;
    }
};

// Concrete Strategy B - Simple Decrement
class ConcreteStrategyB : public Strategy {
public:
    void execute(int& variable1, int& variable2) const override {
        // Simple decrement strategy
        --variable1;
        --variable2;
    }
};

// Context that uses a strategy
class Context {
private:
    std::unique_ptr<Strategy> strategy;

public:
    Context(std::unique_ptr<Strategy> strategy) : strategy(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<Strategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    void executeStrategy(int& variable1, int& variable2) const {
        strategy->execute(variable1, variable2);
    }
};

// GUnit Tests

// Test Strategy Pattern with Concrete Strategy A
TEST(StrategyPatternTests, ConcreteStrategyATest) {
    ConcreteStrategyA strategyA;
    Context context(std::make_unique<ConcreteStrategyA>());

    // Initialize variables
    int variable1 = 5;
    int variable2 = 10;

    // Execute the strategy
    context.executeStrategy(variable1, variable2);

    // Assertions based on the expected behavior of Strategy A
    ASSERT_EQ(variable1, 6);  // Variable 1 should be incremented
    ASSERT_EQ(variable2, 11); // Variable 2 should be incremented
}

// Test Strategy Pattern with Concrete Strategy B
TEST(StrategyPatternTests, ConcreteStrategyBTest) {
    ConcreteStrategyB strategyB;
    Context context(std::make_unique<ConcreteStrategyB>());

    // Initialize variables
    int variable1 = 5;
    int variable2 = 10;

    // Execute the strategy
    context.executeStrategy(variable1, variable2);

    // Assertions based on the expected behavior of Strategy B
    ASSERT_EQ(variable1, 4);  // Variable 1 should be decremented
    ASSERT_EQ(variable2, 9);  // Variable 2 should be decremented
}

// Test Strategy Pattern with Dynamic Strategy Switching
TEST(StrategyPatternTests, DynamicStrategySwitchTest) {
    ConcreteStrategyA strategyA;
    ConcreteStrategyB strategyB;

    Context context(std::make_unique<ConcreteStrategyA>());

    // Initialize variables
    int variable1 = 5;
    int variable2 = 10;

    // Execute the initial strategy (Strategy A)
    context.executeStrategy(variable1, variable2);

    // Switch to a different strategy (Strategy B)
    context.setStrategy(std::make_unique<ConcreteStrategyB>());

    // Execute the new strategy (Strategy B)
    context.executeStrategy(variable1, variable2);

    // Assertions based on the expected behavior of both strategies
    ASSERT_EQ(variable1, 5);   // Variable 1 should be the same since A and B strategies were applied
    ASSERT_EQ(variable2, 10);  // Variable 2 should be the same since A and B strategies were applied
}

// Additional Tests and Assertions

// Test Strategy Pattern with Another Concrete Strategy A Instance
TEST(StrategyPatternTests, AnotherConcreteStrategyATest) {
    ConcreteStrategyA strategyA;
    Context context(std::make_unique<ConcreteStrategyA>());

    // Initialize variables
    int variable1 = 5;
    int variable2 = 10;

    // Execute the strategy
    context.executeStrategy(variable1, variable2);

    // Assertions based on the expected behavior of Another Strategy A instance
    ASSERT_EQ(variable1, 6);  // Variable 1 should be incremented
    ASSERT_EQ(variable2, 11); // Variable 2 should be incremented
}

// Test Strategy Pattern with Another Concrete Strategy B Instance
TEST(StrategyPatternTests, AnotherConcreteStrategyBTest) {
    ConcreteStrategyB strategyB;
    Context context(std::make_unique<ConcreteStrategyB>());

    // Initialize variables
    int variable1 = 5;
    int variable2 = 10;

    // Execute the strategy
    context.executeStrategy(variable1, variable2);

    // Assertions based on the expected behavior of Another Strategy B instance
    ASSERT_EQ(variable1, 4);  // Variable 1 should be decremented
    ASSERT_EQ(variable2, 9);  // Variable 2 should be decremented
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
