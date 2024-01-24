package samples

import (
	"testing"
)

func TestIntegerVariable(t *testing.T) {
	// Declare an integer variable
	var number = 42
 
	// Assert the value of the variable
	if number != 42 {
		t.Errorf("Expected the value of 'number' to be 42, but got %d", number)
	}
}

func TestStringVariable(t *testing.T) {
	// Declare a string variable
	var message = "Hello, Golang!"

	// Assert the value of the variable
	if message != "Hello, Golang!" {
		t.Errorf("Expected the value of 'message' to be 'Hello, Golang!', but got %s", message)
	}
}

func TestBooleanVariable(t *testing.T) {
	// Declare a boolean variable
	var isTrue = true

	// Assert the value of the variable
	if !isTrue {
		t.Error("Expected the value of 'isTrue' to be true, but got false")
	}
}

func TestFloatVariable(t *testing.T) {
	// Declare a float variable
	var pi = 3.14

	// Assert the value of the variable
	if pi != 3.14 {
		t.Errorf("Expected the value of 'pi' to be 3.14, but got %f", pi)
	}
}

func TestMultipleAssignment(t *testing.T) {
	// Declare and assign multiple variables
	x, y := 10, 20

	// Assert the values of the variables
	if x != 10 || y != 20 {
		t.Errorf("Expected values of x and y to be 10 and 20, but got %d and %d", x, y)
	}

	// Intermediate-level: Swap values using multiple assignment
	x, y = y, x

	// Assert the swapped values
	if x != 20 || y != 10 {
		t.Errorf("Expected values of x and y to be swapped, but got %d and %d", x, y)
	}
}

func TestArraySliceVariable(t *testing.T) {
	// Intermediate-level: Declare and manipulate an array and a slice
	var numbers [3]int
	numbers[0] = 1
	numbers[1] = 2
	numbers[2] = 3

	// Assert the length of the array
	if len(numbers) != 3 {
		t.Errorf("Expected the length of 'numbers' array to be 3, but got %d", len(numbers))
	}

	// Declare a slice from the array
	slicedNumbers := numbers[1:]

	// Assert the length of the slice
	if len(slicedNumbers) != 2 {
		t.Errorf("Expected the length of 'slicedNumbers' slice to be 2, but got %d", len(slicedNumbers))
	}
}
