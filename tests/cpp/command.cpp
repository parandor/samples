#include <gtest/gtest.h>

namespace
{

    // Receiver
    class Light
    {
    public:
        bool isOn = false;

        void turnOn()
        {
            isOn = true;
        }

        void turnOff()
        {
            isOn = false;
        }
    };

    // Command interface
    class Command
    {
    public:
        virtual void execute() = 0;
    };

    // Concrete command
    class LightOnCommand : public Command
    {
    private:
        Light &light;

    public:
        LightOnCommand(Light &l) : light(l) {}

        void execute() override
        {
            light.turnOn();
        }
    };

    // Concrete command
    class LightOffCommand : public Command
    {
    private:
        Light &light;

    public:
        LightOffCommand(Light &l) : light(l) {}

        void execute() override
        {
            light.turnOff();
        }
    };

    // Invoker
    class RemoteControl
    {
    private:
        Command *command;

    public:
        void setCommand(Command *cmd)
        {
            command = cmd;
        }

        void pressButton()
        {
            command->execute();
        }
    };

    // Unit Tests
    TEST(CommandPatternTests, LightOnCommandTest)
    {
        Light light;
        LightOnCommand lightOn(light);

        // Execute the command
        lightOn.execute();

        // Test that the light is turned on
        EXPECT_TRUE(light.isOn);
    }

    TEST(CommandPatternTests, LightOffCommandTest)
    {
        Light light;
        LightOffCommand lightOff(light);

        // Execute the command
        lightOff.execute();

        // Test that the light is turned off
        EXPECT_FALSE(light.isOn);
    }

    TEST(CommandPatternTests, RemoteControlTest)
    {
        Light light;
        LightOnCommand lightOn(light);
        RemoteControl remote;

        // Associate command with the invoker
        remote.setCommand(&lightOn);

        // Execute the command
        remote.pressButton();

        // Test that the light is turned on
        EXPECT_TRUE(light.isOn);
    }

    TEST(CommandPatternTests, DynamicCommandChangeTest)
    {
        Light light;
        LightOnCommand lightOn(light);
        LightOffCommand lightOff(light);
        RemoteControl remote;

        // Associate lightOn command with the invoker
        remote.setCommand(&lightOn);

        // Execute the command
        remote.pressButton();

        // Test that the light is turned on
        EXPECT_TRUE(light.isOn);

        // Change the command dynamically to lightOff
        remote.setCommand(&lightOff);

        // Execute the new command
        remote.pressButton();

        // Test that the light is turned off
        EXPECT_FALSE(light.isOn);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
