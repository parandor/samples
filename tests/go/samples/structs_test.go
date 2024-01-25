package samples

import (
	"encoding/json"
	"math"
	"testing"
	"github.com/parandor/samples/types"
)

// Simple struct definition
type Point struct {
	X int
	Y int
}

type Person types.Person

// Test1: Creating an instance of a struct
func TestCreateStructInstance(t *testing.T) {
	// Creating an instance of the Point struct
	point := Point{X: 1, Y: 2}

	// Assertion
	if point.X != 1 || point.Y != 2 {
		t.Errorf("Expected X: 1, Y: 2; Got X: %d, Y: %d", point.X, point.Y)
	}
}

// Test2: Updating struct fields
func TestUpdateStructFields(t *testing.T) {
	// Creating an instance of the Point struct
	point := Point{X: 1, Y: 2}

	// Updating the values
	point.X = 3
	point.Y = 4

	// Assertion
	if point.X != 3 || point.Y != 4 {
		t.Errorf("Expected X: 3, Y: 4; Got X: %d, Y: %d", point.X, point.Y)
	}
}

// Test3: Using a struct with methods
func TestStructWithMethods(t *testing.T) {
	// Creating an instance of the Circle struct
	circle := types.Circle{Radius: 2.5}

	// Calculating the area using the method
	area := circle.Area()

	// Assertion
	expectedArea := math.Pi * 2.5 * 2.5
	if area != expectedArea {
		t.Errorf("Expected Area: %f; Got Area: %f", expectedArea, area)
	}
}

// Nested struct example
type Location struct {
	Latitude  float64
	Longitude float64
}

type Place struct {
	Name     string
	Location Location
}

// Test4: Working with nested structs
func TestNestedStructs(t *testing.T) {
	// Creating an instance of the Place struct with nested Location struct
	home := Place{
		Name: "Home",
		Location: Location{
			Latitude:  37.7749,
			Longitude: -122.4194,
		},
	}

	// Assertion
	if home.Location.Latitude != 37.7749 || home.Location.Longitude != -122.4194 {
		t.Errorf("Unexpected values for Latitude or Longitude in nested struct")
	}
}

// Anonymous struct example
func TestAnonymousStruct(t *testing.T) {
	// Creating an anonymous struct
	person := struct {
		Name    string
		Age     int
		Hobbies []string
	}{
		Name:    "John",
		Age:     30,
		Hobbies: []string{"Reading", "Hiking"},
	}

	// Assertion
	if person.Name != "John" || person.Age != 30 || len(person.Hobbies) != 2 {
		t.Errorf("Unexpected values in anonymous struct")
	}
}

// Array and Slice of Structs
func TestArrayOfStructs(t *testing.T) {
	// Array of Persons
	people := []Person{
		{FirstName: "Bob", LastName: "Smith", Age: 25},
		{FirstName: "Eve", LastName: "Jones", Age: 28},
	}

	// Slice of Persons
	peopleSlice := []Person{
		{FirstName: "Charlie", LastName: "Brown", Age: 32},
		{FirstName: "Diana", LastName: "Miller", Age: 30},
	}

	// Assertion
	if len(people) != 2 || len(peopleSlice) != 2 {
		t.Errorf("Unexpected length of array or slice of structs")
	}
}

// Embedding example
type Employee struct {
	Person  // Embedded struct
	JobRole string
}

// Test5: Working with embedded structs
func TestEmbeddedStructs(t *testing.T) {
	// Creating an instance of the embedded struct with additional field
	manager := Employee{
		Person:  Person{FirstName: "Grace", LastName: "Taylor", Age: 35},
		JobRole: "Manager",
	}

	// Assertion
	if manager.FirstName != "Grace" || manager.JobRole != "Manager" {
		t.Errorf("Unexpected values in embedded struct")
	}
}

// JSON Marshaling/Unmarshaling example
func TestStructJSONMarshalingUnmarshaling(t *testing.T) {
	// Creating an instance of the Person struct
	johnDoe := Person{FirstName: "John", LastName: "Doe", Age: 30}

	// Converting struct to JSON
	jsonData, err := json.Marshal(johnDoe)
	if err != nil {
		t.Errorf("JSON Marshal error: %v", err)
	}

	// Converting JSON to a struct
	var newPerson Person
	err = json.Unmarshal(jsonData, &newPerson)
	if err != nil {
		t.Errorf("JSON Unmarshal error: %v", err)
	}

	// Assertion
	if newPerson.FirstName != "John" || newPerson.Age != 30 {
		t.Errorf("Unexpected values after JSON Marshaling/Unmarshaling")
	}
}

func TestStructJSONTags(t *testing.T) {
	// Creating an instance of the PersonWithTags struct
	janeDoe := Person{FirstName: "Jane", LastName: "Doe", Age: 25}

	// Converting struct to JSON
	jsonData, err := json.Marshal(janeDoe)
	if err != nil {
		t.Errorf("JSON Marshal error: %v", err)
	}

	// Converting JSON to a struct
	var newPerson Person
	err = json.Unmarshal(jsonData, &newPerson)
	if err != nil {
		t.Errorf("JSON Unmarshal error: %v", err)
	}

	// Assertion
	if newPerson.FirstName != "Jane" || newPerson.Age != 25 {
		t.Errorf("Unexpected values after JSON Marshaling/Unmarshaling with tags")
	}
}

// Test7: Using JSON tags to control field names in JSON with embedded struct
type EmployeeWithTags struct {
	Person         // Embedded struct with tags
	JobRole string `json:"job_role"`
}

func TestStructEmbeddedStructsWithTags(t *testing.T) {
	// Creating an instance of the embedded struct with tags and additional field
	seniorDev := EmployeeWithTags{
		Person:  Person{FirstName: "Mark", LastName: "Johnson", Age: 40},
		JobRole: "Senior Developer",
	}

	// Converting struct to JSON
	jsonData, err := json.Marshal(seniorDev)
	if err != nil {
		t.Errorf("JSON Marshal error: %v", err)
	}

	// Converting JSON to a struct
	var newEmployee EmployeeWithTags
	err = json.Unmarshal(jsonData, &newEmployee)
	if err != nil {
		t.Errorf("JSON Unmarshal error: %v", err)
	}

	// Assertion
	if newEmployee.FirstName != "Mark" || newEmployee.JobRole != "Senior Developer" {
		t.Errorf("Unexpected values after JSON Marshaling/Unmarshaling with tags and embedded struct")
	}
}

func TestStructShapeInterface(t *testing.T) {
	// Creating an instance of the Rectangle struct
	rect := types.Rectangle{Width: 5, Height: 10}

	// Calculating the area using the TotalArea function
	totalArea := types.TotalArea(&rect)
	expectedArea := rect.Area()

	// Assertion
	if totalArea != expectedArea {
		t.Errorf("Expected Area: %f; Got Total Area: %f", expectedArea, totalArea)
	}
}

// Test9: Using anonymous struct and array of structs
func TestStructsAnonymousStructAndArray(t *testing.T) {
	// Creating an anonymous struct
	person := struct {
		Name    string
		Age     int
		Hobbies []string
	}{
		Name:    "Alice",
		Age:     28,
		Hobbies: []string{"Reading", "Painting"},
	}

	// Array of anonymous structs
	people := []struct {
		Name    string
		Age     int
		Hobbies []string
	}{
		{"Bob", 30, []string{"Hiking", "Photography"}},
		{"Charlie", 25, []string{"Coding", "Gaming"}},
	}

	// Assertion
	if person.Name != "Alice" || len(people) != 2 {
		t.Errorf("Unexpected values in anonymous struct or array of structs")
	}
}

// This test demonstrates the process of marshaling an anonymous struct to JSON
// and then unmarshaling the JSON data back into a different struct with the
// same structure.
func TestStructsJSONAnonymous(t *testing.T) {
	// Creating an anonymous struct
	data := struct {
		Title  string   `json:"title"`
		Author string   `json:"author"`
		Tags   []string `json:"tags"`
	}{
		Title:  "Golang Basics",
		Author: "John Doe",
		Tags:   []string{"Programming", "Golang", "Tutorial"},
	}

	// Converting struct to JSON
	jsonData, err := json.Marshal(data)
	if err != nil {
		t.Errorf("JSON Marshal error: %v", err)
	}

	// Converting JSON to a struct
	var newData struct {
		Title  string   `json:"title"`
		Author string   `json:"author"`
		Tags   []string `json:"tags"`
	}
	err = json.Unmarshal(jsonData, &newData)
	if err != nil {
		t.Errorf("JSON Unmarshal error: %v", err)
	}

	// Assertion
	if newData.Title != "Golang Basics" || newData.Author != "John Doe" || len(newData.Tags) != 3 {
		t.Errorf("Unexpected values after JSON Marshaling/Unmarshaling with anonymous struct")
	}
}
