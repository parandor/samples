/*
 * File: serialization.cpp
 * Author: Peter Arandorenko
 * Date: 2024-01-20
 * Description: C++ unit tests showcasing serialization use cases using JSON and binary serialization.
 */

#include <gtest/gtest.h>
#include <sstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <nlohmann/json.hpp>

// Class representing a person with name, age, and email attributes
class Person
{
public:
    Person() = default;
    Person(const std::string &name, int age, const std::string &email)
        : name(name), age(age), email(email) {}

    const std::string &getName() const { return name; }
    int getAge() const { return age; }
    const std::string &getEmail() const { return email; }

    bool operator==(const Person &other) const
    {
        return name == other.name && age == other.age && email == other.email;
    }

private:
    std::string name;
    int age;
    std::string email;

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & name;
        ar & age;
        ar & email;
    }
};

// JSON Serialization and Deserialization Functions
std::string serializeToJson(const Person &person)
{
    nlohmann::json jsonPerson;
    jsonPerson["name"] = person.getName();
    jsonPerson["age"] = person.getAge();
    jsonPerson["email"] = person.getEmail();
    return jsonPerson.dump();
}

Person deserializeFromJson(const std::string &jsonStr)
{
    nlohmann::json jsonPerson = nlohmann::json::parse(jsonStr);
    return Person(jsonPerson["name"], jsonPerson["age"], jsonPerson["email"]);
}

// Binary Serialization and Deserialization Functions
std::string serializeToBinary(const Person &person)
{
    std::ostringstream oss;
    boost::archive::binary_oarchive archive(oss);
    archive << person;
    return oss.str();
}

Person deserializeFromBinary(const std::string &binaryData)
{
    std::istringstream iss(binaryData);
    boost::archive::binary_iarchive archive(iss);
    Person deserializedPerson;
    archive >> deserializedPerson;
    return deserializedPerson;
}

// Tests
TEST(SerializationTest, JSONSerialization)
{
    Person person("John", 25, "john@example.com");
    std::string jsonSerializedData = serializeToJson(person);
    Person jsonDeserializedPerson = deserializeFromJson(jsonSerializedData);
    ASSERT_EQ(person, jsonDeserializedPerson);
}

TEST(SerializationTest, BinarySerialization)
{
    Person person("Alice", 30, "alice@example.com");
    std::string binarySerializedData = serializeToBinary(person);
    Person binaryDeserializedPerson = deserializeFromBinary(binarySerializedData);
    ASSERT_EQ(person, binaryDeserializedPerson);
}

// Main function to run the tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
