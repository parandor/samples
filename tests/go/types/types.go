package types

import (
	"fmt"
	"math"
)

// Person struct definition
type Person struct {
	FirstName string `json:"first_name"`
	LastName  string `json:"last_name"`
	Age       int    `json:"age"`
}

// Shape is an interface representing a geometric shape.
type Shape interface {
	Area() float64
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

// Circle is a type that implements the Shape interface.
type Circle struct {
	Radius float64
}


// Stringer is an interface representing types that can be converted to a string.
type Stringer interface {
	String() string
}

// MyType is an example type that satisfies the Stringer interface.
type MyType int

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

// String method for MyType converts it to a string.
func (mt MyType) String() string {
	return fmt.Sprintf("MyType: %d", mt)
}


