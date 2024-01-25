package samples

import (
	"fmt"
	"math"
	"testing"
)

// Shape is an interface representing a geometric shape.
type Shape interface {
	Area() float64
}

// ReadWriteCloser is an example interface with embedding.
// The ReadWriteCloser interface embeds the Shape interface. This means any type
// implementing ReadWriteCloser must also implement the Area method from the Shape
// interface. Additionally, it introduces a new method Close(), which returns an error.
// So, a type that implements ReadWriteCloser is expected to provide implementations
// for both Area() and Close() methods.
//
// An interface defines a set of methods, and any type that implements those methods
// implicitly satisfies the interface.
// A type can implement multiple interfaces, enabling it to play different roles in
// the program.

type ReadWriteCloser interface {
	Shape
	Close() error
}

// Rectangle is a type that implements the Shape interface.
type Rectangle struct {
	Width  float64
	Height float64
}

// Area method for Rectangle calculates the area of the rectangle.
// When you define a method on a value receiver (as in func (r Rectangle) Area() float64),
// you can call that method on both values and pointers to that type
func (r Rectangle) Area() float64 {
	return r.Width * r.Height
}

// Close method for Rectangle satisfies the Close method of ReadWriteCloser.
func (r Rectangle) Close() error {
	// Implement close logic here
	fmt.Println("Closing the rectangle")
	return nil
}

// Circle is a type that implements the Shape interface.
type Circle struct {
	Radius float64
}

// Area method for Circle calculates the area of the circle.
func (c Circle) Area() float64 {
	return math.Pi * c.Radius * c.Radius
}

// Close method for Circle satisfies the Close method of ReadWriteCloser.
func (c Circle) Close() error {
	// Implement close logic here
	fmt.Println("Closing the circle")
	return nil
}

// Stringer is an interface representing types that can be converted to a string.
type Stringer interface {
	String() string
}

// MyType is an example type that satisfies the Stringer interface.
type MyType int

// String method for MyType converts it to a string.
func (mt MyType) String() string {
	return fmt.Sprintf("MyType: %d", mt)
}

// TotalArea calculates the total area of multiple shapes.
func TotalArea(shapes ...Shape) float64 {
	total := 0.0
	for _, shape := range shapes {
		if shape != nil {
			total += shape.Area()
		}
	}
	return total
}

// identity is an example function using an empty interface as a generic type.
func identity(value interface{}) interface{} {
	return value
}

// printAnyValue is an example function using an empty interface.
func printAnyValue(value interface{}) {
	fmt.Println(value)
}

// TestRectangleArea tests the Area method for Rectangle.
func TestRectangleArea(t *testing.T) {
	rect := Rectangle{Width: 5, Height: 10}
	result := rect.Area()
	expected := 50.0

	if result != expected {
		t.Errorf("Expected: %f, Got: %f", expected, result)
	}
}

// TestCircleArea tests the Area method for Circle.
func TestCircleArea(t *testing.T) {
	circle := Circle{Radius: 3}
	result := circle.Area()
	expected := math.Pi * 3 * 3

	if result != expected {
		t.Errorf("Expected: %f, Got: %f", expected, result)
	}
}

// TestTotalArea tests the TotalArea function with multiple shapes.
func TestTotalArea(t *testing.T) {
	rect := Rectangle{Width: 5, Height: 10}
	circle := Circle{Radius: 3}

	result := TotalArea(rect, circle)
	expected := rect.Area() + circle.Area()

	if result != expected {
		t.Errorf("Expected: %f, Got: %f", expected, result)
	}
}

// TestTotalAreaNoShapes tests the TotalArea function with no shapes.
func TestTotalAreaNoShapes(t *testing.T) {
	result := TotalArea()
	expected := 0.0

	if result != expected {
		t.Errorf("Expected: %f, Got: %f", expected, result)
	}
}

// TestEmptyInterface demonstrates the usage of empty interfaces.
func TestEmptyInterface(t *testing.T) {
	// No direct comparison as it involves printing
	printAnyValue(42)
	printAnyValue("Hello, Go!")
	printAnyValue([]int{1, 2, 3})
}

// TestTypeAssertion demonstrates type assertion on interfaces.
func TestTypeAssertion(t *testing.T) {
	var val interface{} = 42
	result, ok := val.(int)

	if !ok || result != 42 {
		t.Errorf("Expected: %d, Got: %v", 42, result)
	}
}

// TestTypeSwitch demonstrates the usage of a type switch on interfaces.
func TestTypeSwitch(t *testing.T) {
	values := []interface{}{42, "Go", 3.14}

	for _, v := range values {
		switch val := v.(type) {
		case int:
			fmt.Printf("Integer: %d\n", val)
		case string:
			fmt.Printf("String: %s\n", val)
		case float64:
			fmt.Printf("Float: %f\n", val)
		default:
			fmt.Println("Unknown type")
		}
	}
}

// TestInterfaceEmbedding demonstrates interface embedding.
func TestInterfaceEmbedding(t *testing.T) {
	rect := Rectangle{Width: 5, Height: 10}
	var rwCloser ReadWriteCloser = rect

	areaResult := rwCloser.Area()
	closeResult := rwCloser.Close()

	expectedArea := rect.Area()
	expectedClose := rect.Close()

	// Check if the Area result matches the expected result
	if areaResult != expectedArea {
		t.Errorf("Expected Area: %f, Got: %f", expectedArea, areaResult)
	}

	// Check if the Close result matches the expected result
	if closeResult != expectedClose {
		t.Errorf("Expected Close result: %v, Got: %v", expectedClose, closeResult)
	}
}

// TestEmptyInterfaceAsGenericType demonstrates using an empty interface as a generic type.
func TestEmptyInterfaceAsGenericType(t *testing.T) {
	result := identity(42)
	expected := 42

	if result != expected {
		t.Errorf("Expected: %v, Got: %v", expected, result)
	}
}

// TestInterfaceSatisfactionImplicitly demonstrates interface satisfaction implicitly.
func TestInterfaceSatisfactionImplicitly(t *testing.T) {
	var s Stringer = MyType(42)
	result := s.String()
	expected := "MyType: 42"

	if result != expected {
		t.Errorf("Expected: %s, Got: %s", expected, result)
	}
}

// func main() {
// 	// Run the tests
// 	t := new(testing.T)
// 	TestRectangleArea(t)
// 	TestCircleArea(t)
// 	TestTotalArea(t)
// 	TestTotalAreaNoShapes(t)
// 	TestTotalAreaNilShape(t)
// 	TestEmptyInterface(t)
// 	TestTypeAssertion(t)
// 	TestTypeSwitch(t)
// 	TestInterfaceEmbedding(t)
// 	TestEmptyInterfaceAsGenericType(t)
// 	TestInterfaceSatisfactionImplicitly(t)
// }
