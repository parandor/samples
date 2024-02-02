#include <gtest/gtest.h>

namespace
{
    // Component interface
    class Coffee
    {
    public:
        virtual ~Coffee() = default;
        virtual void brew() const = 0;
    };

    // Concrete component
    class SimpleCoffee : public Coffee
    {
    public:
        void brew() const override
        {
            std::cout << "Brewing simple coffee." << std::endl;
        }
    };

    // Decorator interface
    class CoffeeDecorator : public Coffee
    {
    private:
        Coffee *coffee;

    public:
        CoffeeDecorator(Coffee *c) : coffee(c) {}

        void brew() const override
        {
            coffee->brew();
        }
    };

    // Concrete decorators
    class MilkDecorator : public CoffeeDecorator
    {
    public:
        MilkDecorator(Coffee *c) : CoffeeDecorator(c) {}

        void addMilk() const
        {
            std::cout << "Adding milk." << std::endl;
        }

        void brew() const override
        {
            CoffeeDecorator::brew();
            addMilk();
        }
    };

    class SugarDecorator : public CoffeeDecorator
    {
    public:
        SugarDecorator(Coffee *c) : CoffeeDecorator(c) {}

        void addSugar() const
        {
            std::cout << "Adding sugar." << std::endl;
        }

        void brew() const override
        {
            CoffeeDecorator::brew();
            addSugar();
        }
    };

    // Google Test Fixture
    class DecoratorPatternTests : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // Initialization code goes here
        }

        void TearDown() override
        {
            // Clean-up code goes here
        }
    };

    // Google Test Cases
    TEST_F(DecoratorPatternTests, SimpleCoffeeTest)
    {
        SimpleCoffee simpleCoffee;
        testing::internal::CaptureStdout(); // Redirect cout for assertion

        // Test brewing simple coffee
        simpleCoffee.brew();

        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "Brewing simple coffee.\n");
    }

    TEST_F(DecoratorPatternTests, MilkDecoratorTest)
    {
        SimpleCoffee simpleCoffee;
        MilkDecorator milkCoffee(&simpleCoffee);
        testing::internal::CaptureStdout(); // Redirect cout for assertion

        // Test brewing coffee with milk
        milkCoffee.brew();

        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "Brewing simple coffee.\nAdding milk.\n");
    }

    TEST_F(DecoratorPatternTests, MilkAndSugarDecoratorTest)
    {
        SimpleCoffee simpleCoffee;
        MilkDecorator milkCoffee(&simpleCoffee);
        SugarDecorator sweetCoffee(&milkCoffee);
        testing::internal::CaptureStdout(); // Redirect cout for assertion

        // Test brewing sweet coffee with milk and sugar
        sweetCoffee.brew();

        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "Brewing simple coffee.\nAdding milk.\nAdding sugar.\n");
    }

    TEST_F(DecoratorPatternTests, MultipleMilkDecoratorTest)
    {
        SimpleCoffee simpleCoffee;
        MilkDecorator firstMilk(&simpleCoffee);
        MilkDecorator secondMilk(&firstMilk);
        testing::internal::CaptureStdout(); // Redirect cout for assertion

        // Test brewing coffee with multiple milk decorators
        secondMilk.brew();

        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "Brewing simple coffee.\nAdding milk.\nAdding milk.\n");
    }

    TEST_F(DecoratorPatternTests, MixAndMatchDecoratorsTest)
    {
        SimpleCoffee simpleCoffee;
        MilkDecorator milkCoffee(&simpleCoffee);
        SugarDecorator sweetCoffee(&milkCoffee);
        MilkDecorator doubleMilkSugarCoffee(&sweetCoffee);
        testing::internal::CaptureStdout(); // Redirect cout for assertion

        // Test brewing coffee with a mix of decorators
        doubleMilkSugarCoffee.brew();

        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "Brewing simple coffee.\nAdding milk.\nAdding sugar.\nAdding milk.\n");
    }

    // Additional tests can be added similarly
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
