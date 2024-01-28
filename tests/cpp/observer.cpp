// Comments explaining Observer Design Pattern

// The Observer design pattern is a behavioral pattern where an object, known
// as the subject, maintains a list of its dependents, known as observers, that
// are notified of state changes, typically by calling one of their methods.

// Use Cases:

// 1. **Decoupling:**
//    When there is a need to decouple an abstraction from its implementation so
//    that two aspects of a system can vary independently.

// 2. **Event Handling:**
//    When you want to implement distributed event handling systems, such as in
//    graphical user interfaces, where a change in one object leads to updates
//    in multiple dependent objects.

// 3. **Notification Systems:**
//    When you need a notification mechanism between objects without making them
//    tightly coupled, enabling a flexible and reusable communication pattern.

// 4. **Monitoring and Logging:**
//    When you want to implement monitoring and logging functionalities where an
//    object needs to notify multiple observers about its state changes.

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

// Subject interface
class Subject {
public:
    virtual ~Subject() = default;
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers(const std::string& message) = 0;
};

// Concrete Observer
class ConcreteObserver : public Observer {
public:
    std::string state;

    void update(const std::string& message) override {
        // Process the update from the subject
        // (In a real-world scenario, this could involve reacting to the message)
        state = message;
    }
};

// Concrete Subject
class ConcreteSubject : public Subject {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        auto it = std::remove(observers.begin(), observers.end(), observer);
        observers.erase(it, observers.end());
    }

    void notifyObservers(const std::string& message) override {
        for (auto observer : observers) {
            observer->update(message);
        }
    }
};

// GUnit Tests

// Test Observer Pattern
TEST(ObserverPatternTests, ObserverPatternTest) {
    ConcreteSubject subject;

    ConcreteObserver observer1;
    ConcreteObserver observer2;

    subject.addObserver(&observer1);
    subject.addObserver(&observer2);

    // Notify observers about a state change
    subject.notifyObservers("State has changed");

    // In a real-world scenario, you would assert that observers have been appropriately updated
    ASSERT_EQ(observer1.state, "State has changed");
    ASSERT_EQ(observer2.state, "State has changed");
}

// Test Observer Pattern with Removal
TEST(ObserverPatternTests, ObserverPatternRemovalTest) {
    ConcreteSubject subject;

    ConcreteObserver observer1;
    ConcreteObserver observer2;

    subject.addObserver(&observer1);
    subject.addObserver(&observer2);

    // Notify observers about a state change
    subject.notifyObservers("State has changed");

    // Remove observer1 and notify again
    subject.removeObserver(&observer1);
    subject.notifyObservers("Another state change");

    // In a real-world scenario, you would assert that observer1 didn't receive the second notification
    ASSERT_EQ(observer1.state, "State has changed");
    ASSERT_EQ(observer2.state, "Another state change");
}

// Test Observer Pattern with No Observers
TEST(ObserverPatternTests, ObserverPatternNoObserversTest) {
    ConcreteSubject subject;

    // Notify without any observers
    subject.notifyObservers("State has changed");

    // In a real-world scenario, you would assert that there are no issues when no observers are present
    ASSERT_EQ(observer1.state, "");
    ASSERT_EQ(observer2.state, "");
}

// Test Observer Pattern with Multiple Notifications
TEST(ObserverPatternTests, ObserverPatternMultipleNotificationsTest) {
    ConcreteSubject subject;

    ConcreteObserver observer1;
    ConcreteObserver observer2;

    subject.addObserver(&observer1);
    subject.addObserver(&observer2);

    // Notify observers multiple times
    subject.notifyObservers("State has changed");
    subject.notifyObservers("Another state change");

    // In a real-world scenario, you would assert that observers received both notifications
    ASSERT_EQ(observer1.state, "Another state change");
    ASSERT_EQ(observer2.state, "Another state change");
}

// Test Observer Pattern with Different Subjects
TEST(ObserverPatternTests, ObserverPatternDifferentSubjectsTest) {
    ConcreteSubject subject1;
    ConcreteSubject subject2;

    ConcreteObserver observer;

    subject1.addObserver(&observer);

    // Notify observer with changes from subject1
    subject1.notifyObservers("State change in Subject 1");

    // Observer is not subscribed to subject2, so no notification should occur
    subject2.notifyObservers("State change in Subject 2");

    // In a real-world scenario, you would assert that observer only received updates from subject1
    ASSERT_EQ(observer1.state, "State change in Subject 1");
    ASSERT_EQ(observer2.state, "");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
