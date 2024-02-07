package samples

import (
	"reflect"
	"testing"
)

// Beginner level: Test for checking if a variable is a string.
func TestIsString(t *testing.T) {
	str := "hello"
	if reflect.TypeOf(str).Kind() != reflect.String {
		t.Errorf("Expected a string type but got %v", reflect.TypeOf(str).Kind())
	}
}

// Beginner level: Test for checking if a variable is an integer.
func TestIsInteger(t *testing.T) {
	num := 42
	if reflect.TypeOf(num).Kind() != reflect.Int {
		t.Errorf("Expected an integer type but got %v", reflect.TypeOf(num).Kind())
	}
}

// Intermediate level: Test for checking if a variable is a slice.
func TestIsSlice(t *testing.T) {
	slice := []int{1, 2, 3}
	if reflect.TypeOf(slice).Kind() != reflect.Slice {
		t.Errorf("Expected a slice type but got %v", reflect.TypeOf(slice).Kind())
	}
}

type MyStruct struct {
	Name             string
	SomeMethodString string
}

// Define the SetName method in the MyStruct type.
func (s *MyStruct) SetName(name string) {
	s.Name = name
}

func (s *MyStruct) SomeMethod(someString string) {
	s.SomeMethodString = someString
}

// Intermediate level: Test for checking if a method exists in a struct.
func TestMethodExists(t *testing.T) {
	s := MyStruct{}
	method := reflect.ValueOf(&s).MethodByName("SomeMethod")
	if !method.IsValid() {
		t.Errorf("Expected method SomeMethod to exist but it does not.")
	}
}

// Advanced level: Test for dynamically invoking a method on a struct using reflection.
func TestInvokeMethod(t *testing.T) {

	s := MyStruct{Name: "John"}
	method := reflect.ValueOf(&s).MethodByName("SetName")
	args := []reflect.Value{reflect.ValueOf("Doe")}
	method.Call(args)
	if s.Name != "Doe" {
		t.Errorf("Expected Name to be 'Doe' but got %s", s.Name)
	}
}

// Advanced level: Test for dynamically setting a value of a struct field using reflection.
func TestSetFieldValue(t *testing.T) {
	type Person struct {
		Name string
	}
	p := Person{Name: "Alice"}
	field := reflect.ValueOf(&p).Elem().FieldByName("Name")
	if field.IsValid() && field.CanSet() {
		field.SetString("Bob")
	} else {
		t.Errorf("Unable to set field value.")
	}
	if p.Name != "Bob" {
		t.Errorf("Expected Name to be 'Bob' but got %s", p.Name)
	}
}
