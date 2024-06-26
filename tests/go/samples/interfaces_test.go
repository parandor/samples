package samples

import (
	"fmt"
	"math"
	"testing"
	"github.com/parandor/samples/tests/go/types"
)

// identity is an example function using an empty interface as a generic type.
func identity(value interface{}) interface{} {
	return value
}

// printAnyValue is an example function using an empty interface.
func printAnyValue(value interface{}) {
	fmt.Println(value)
}

// TestRectangleArea tests the Area method for Rectangle.
func TestInterfacesRectangleArea(t *testing.T) {
	rect := types.Rectangle{Width: 5, Height: 10}
	result := rect.Area()
	expected := 50.0

	if result != expected {
		t.Errorf("Expected: %f, Got: %f", expected, result)
	}
}

// TestCircleArea tests the Area method for Circle.
func TestInterfacesCircleArea(t *testing.T) {
	circle := types.Circle{Radius: 3}
	result := circle.Area()
	expected := math.Pi * 3 * 3

	if result != expected {
		t.Errorf("Expected: %f, Got: %f", expected, result)
	}
}

// TestTotalArea tests the TotalArea function with multiple shapes.
func TestInterfacesTotalArea(t *testing.T) {
	rect := types.Rectangle{Width: 5, Height: 10}
	circle := types.Circle{Radius: 3}

	result := types.TotalArea(rect, circle)
	expected := rect.Area() + circle.Area()

	if result != expected {
		t.Errorf("Expected: %f, Got: %f", expected, result)
	}
}

// TestTotalAreaNoShapes tests the TotalArea function with no shapes.
func TestInterfacesTotalAreaNoShapes(t *testing.T) {
	result := types.TotalArea()
	expected := 0.0

	if result != expected {
		t.Errorf("Expected: %f, Got: %f", expected, result)
	}
}

// TestEmptyInterface demonstrates the usage of empty interfaces.
func TestInterfacesEmptyInterface(t *testing.T) {
	// No direct comparison as it involves printing
	printAnyValue(42)
	printAnyValue("Hello, Go!")
	printAnyValue([]int{1, 2, 3})
}

// TestTypeAssertion demonstrates type assertion on interfaces.
func TestInterfacesTypeAssertion(t *testing.T) {
	var val interface{} = 42
	result, ok := val.(int)

	if !ok || result != 42 {
		t.Errorf("Expected: %d, Got: %v", 42, result)
	}
}

// TestTypeSwitch demonstrates the usage of a type switch on interfaces.
func TestInterfacesTypeSwitch(t *testing.T) {
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
func TestInterfacesEmbedding(t *testing.T) {
	rect := types.Rectangle{Width: 5, Height: 10}
	var rwCloser types.ReadWriteCloser = rect

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
func TestInterfacesEmptyInterfaceAsGenericType(t *testing.T) {
	result := identity(42)
	expected := 42

	if result != expected {
		t.Errorf("Expected: %v, Got: %v", expected, result)
	}
}

// TestInterfaceSatisfactionImplicitly demonstrates interface satisfaction implicitly.
func TestInterfacesSatisfactionImplicitly(t *testing.T) {
	var s types.Stringer = types.MyType(42)
	result := s.String()
	expected := "MyType: 42"

	if result != expected {
		t.Errorf("Expected: %s, Got: %s", expected, result)
	}
}

// Printer is an interface with a Print method.
type Printer interface {
	Print() string
}

// Document represents a printable document.
type Document struct {
	Title string
}

// Print method for Document.
func (d Document) Print() string {
	return fmt.Sprintf("Printing document: %s", d.Title)
}

// Image represents a printable image.
type Image struct {
	Name string
}

// Print method for Image.
func (i Image) Print() string {
	return fmt.Sprintf("Printing image: %s", i.Name)
}

// PrintWithAssertion prints the content using type assertion based on the underlying type.
func PrintWithAssertion(p interface{}) string {
	switch v := p.(type) {
	case Printer:
		return v.Print()
	default:
		return "Unsupported type"
	}
}

// TestTypeAssertion demonstrates type assertion in the context of the Printer interface.
func TestInterfacesTypeAssertionAdvanced(t *testing.T) {
	document := Document{Title: "GoLang Basics"}
	image := Image{Name: "Nature.jpg"}

	// Testing type assertion with Document
	documentResult := PrintWithAssertion(document)
	if documentResult != "Printing document: GoLang Basics" {
		t.Errorf("Unexpected result for Document. Got: %s", documentResult)
	}

	// Testing type assertion with Image
	imageResult := PrintWithAssertion(image)
	if imageResult != "Printing image: Nature.jpg" {
		t.Errorf("Unexpected result for Image. Got: %s", imageResult)
	}

	// Testing type assertion with unsupported type
	unsupportedResult := PrintWithAssertion("Unsupported")
	if unsupportedResult != "Unsupported type" {
		t.Errorf("Unexpected result for unsupported type. Got: %s", unsupportedResult)
	}
}