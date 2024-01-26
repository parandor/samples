package samples

import (
	"fmt"
	"testing"
)

// Rectangle represents a rectangle with width and height.
type Rectangle struct {
	Width  float64
	Height float64
}

// Method to calculate the area of a rectangle.
func (r Rectangle) Area() float64 {
	return r.Width * r.Height
}

// TestMethodInvocation tests invoking a basic method on a struct.
func TestMethodInvocation(t *testing.T) {
	rect := Rectangle{Width: 5.0, Height: 3.0}
	area := rect.Area()

	// Asserting the calculated area
	if area != 15.0 {
		t.Errorf("Expected area of 15.0, but got %f", area)
	}
}

// Circle represents a circle with radius.
type Circle struct {
	Radius float64
}

// Method to calculate the area of a circle.
func (c Circle) Area() float64 {
	return 3.14 * c.Radius * c.Radius
}

// TestMethodOverloading tests method overloading using different receiver types.
func TestMethodOverloading(t *testing.T) {
	rect := Rectangle{Width: 5.0, Height: 3.0}
	circle := Circle{Radius: 2.0}

	// Calculating area for both rectangle and circle
	rectArea := rect.Area()
	circleArea := circle.Area()

	// Asserting the calculated areas
	if rectArea != 15.0 {
		t.Errorf("Expected rectangle area of 15.0, but got %f", rectArea)
	}

	if circleArea != 12.56 {
		t.Errorf("Expected circle area of 12.56, but got %f", circleArea)
	}
}

// TestPointerReceiver tests using a pointer receiver for modifying the struct.
func TestMethodPointerReceiver(t *testing.T) {
	rect := Rectangle{Width: 5.0, Height: 3.0}
	rect.Scale(2.0)

	// Asserting the modified width
	if rect.Width != 10.0 {
		t.Errorf("Expected modified width of 10.0, but got %f", rect.Width)
	}
}

// Method to scale the width of a rectangle using a pointer receiver.
func (r *Rectangle) Scale(factor float64) {
	r.Width *= factor
}

// TestInterfaceMethod tests using interfaces and method sets.
func TestMethodInterfaceMethod(t *testing.T) {
	// Assigning a rectangle to the interface
	var shape = Rectangle{Width: 5.0, Height: 3.0}
	area := shape.Area()

	// Asserting the calculated area
	if area != 15.0 {
		t.Errorf("Expected area of 15.0, but got %f", area)
	}
}

// Shape is an interface with an Area method.
type Shape interface {
	Area() float64
}

// TestAdvancedMethodUsage showcases an advanced example of using methods.
func TestMethodAdvancedUsage(t *testing.T) {
	rect := NewRectangle(5.0, 3.0)
	fmt.Println(rect.GetDescription())

	// Creating a RectangleWithDescription using method chaining
	description := rect.
		SetWidth(8.0).
		SetHeight(4.0).
		SetDescription("An updated rectangle")

	fmt.Println(description)
}

// RectangleWithDescription represents a rectangle with a description.
type RectangleWithDescription struct {
	Rectangle
	Description string
}

// Method to create a new rectangle with a description.
func NewRectangle(width, height float64) RectangleWithDescription {
	return RectangleWithDescription{
		Rectangle:   Rectangle{Width: width, Height: height},
		Description: "A rectangle",
	}
}

// Method to set the description of the rectangle.
func (r RectangleWithDescription) SetDescription(description string) RectangleWithDescription {
	r.Description = description
	return r
}

// Method to get a description of the rectangle.
func (r RectangleWithDescription) GetDescription() string {
	return fmt.Sprintf("%s with width %.2f and height %.2f.", r.Description, r.Width, r.Height)
}

// Method to set the width of the rectangle.
func (r RectangleWithDescription) SetWidth(width float64) RectangleWithDescription {
	r.Width = width
	return r
}

// Method to set the height of the rectangle.
func (r RectangleWithDescription) SetHeight(height float64) RectangleWithDescription {
	r.Height = height
	return r
}

// Calculator represents a simple calculator.
type Calculator struct{}

// CalculateSum calculates the sum of a variable number of integers.
func (c Calculator) CalculateSum(nums ...int) int {
	sum := 0
	for _, num := range nums {
		sum += num
	}
	return sum
}

// TestCalculateSum tests the variadic method CalculateSum.
func TestMethodVariadicCalculateSum(t *testing.T) {
	calculator := Calculator{}

	// Testing with different numbers of arguments
	sum1 := calculator.CalculateSum(1, 2, 3)
	sum2 := calculator.CalculateSum(4, 5, 6, 7)
	sum3 := calculator.CalculateSum(8, 9)

	// Asserting the calculated sums
	if sum1 != 6 {
		t.Errorf("Expected sum of 6, but got %d", sum1)
	}

	if sum2 != 22 {
		t.Errorf("Expected sum of 22, but got %d", sum2)
	}

	if sum3 != 17 {
		t.Errorf("Expected sum of 17, but got %d", sum3)
	}
}
