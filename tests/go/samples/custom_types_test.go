package samples

import (
    "testing"
    "github.com/stretchr/testify/assert"
    "github.com/parandor/samples/tests/go/types"
)

type Celsius types.Celsius
type Fahrenheit types.Fahrenheit

// Define a method to convert Celsius to Fahrenheit.
func (c Celsius) ToFahrenheit() Fahrenheit {
    return Fahrenheit(c*9/5 + 32)
}

// Beginner level: Test for creating a custom type.
func TestCustomTypeCreation(t *testing.T) {

    // Create a variable of the custom type.
    temperature := Celsius(25.0)
    
    // Assert that the value and type of the variable match the custom type.
    assert.Equal(t, Celsius(25.0), temperature, "Expected temperature to be 25.0")
}

// Beginner level: Test for type conversion of custom types.
func TestTypeConversion(t *testing.T) {

    // Create a variable of type Celsius.
    celsius := Celsius(25.0)
    
    // Convert Celsius to Fahrenheit.
    fahrenheit := Fahrenheit(celsius*9/5 + 32)
    
    // Assert the value of Fahrenheit temperature.
    assert.Equal(t, Fahrenheit(77.0), fahrenheit, "Expected temperature to be 77.0 Fahrenheit")
}

// Intermediate level: Test for method declaration on custom types.
func TestCustomTypeMethod(t *testing.T) {

    // Create a variable of type Celsius.
    celsius := Celsius(25.0)

    // Call the method on the Celsius variable.
    fahrenheit := celsius.ToFahrenheit()

    // Assert the value of Fahrenheit temperature.
    assert.Equal(t, Fahrenheit(77.0), fahrenheit, "Expected temperature to be 77.0 Fahrenheit")
}

// Implement the Temperature interface for Celsius.
func (c Celsius) GetTemperature() float64 {
    return float64(c)
}

// Advanced level: Test for implementing an interface with a custom type.
func TestCustomTypeInterfaceImplementation(t *testing.T) {
    // Define an interface for measuring temperature.
    type Temperature interface {
        GetTemperature() float64
    }
    
    // Create a variable of type Celsius.
    celsius := Celsius(25.0)
    
    // Assert that Celsius implements the Temperature interface.
    var temp Temperature = celsius
    assert.Equal(t, 25.0, temp.GetTemperature(), "Expected temperature to be 25.0")
}

// Advanced level: Test for embedding custom types.
func TestCustomTypeEmbedding(t *testing.T) {
    // Define a custom type representing a location with latitude and longitude.
    type Location struct {
        Latitude  float64
        Longitude float64
    }
    
    // Define a custom type representing a city with a name and location.
    type City struct {
        Name     string
        Location // Embedding Location type
    }
    
    // Create a variable of type City.
    city := City{
        Name: "New York",
        Location: Location{
            Latitude:  40.7128,
            Longitude: -74.0060,
        },
    }
    
    // Assert the values of city name, latitude, and longitude.
    assert.Equal(t, "New York", city.Name, "Expected city name to be New York")
    assert.Equal(t, 40.7128, city.Latitude, "Expected latitude to be 40.7128")
    assert.Equal(t, -74.0060, city.Longitude, "Expected longitude to be -74.0060")
}
