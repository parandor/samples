package samples

import "testing"

// Summary: Go Pointers Usage
//
// This Go file contains sample unit tests showcasing various aspects of pointers in the Go language.
// Pointers are used in Go for referencing and manipulating memory, allowing efficient and flexible
// programming. The tests cover basic to advanced scenarios, including pointer initialization, assignment,
// dereferencing, working with structs, and using pointers as function parameters. Additionally, nil
// pointer checks are included to ensure safety when working with pointers.

type Person struct {
    Name string
    Age  int
}

// TestPointerInitialization checks pointer initialization and ensures it starts with zero value.
func TestPointerInitialization(t *testing.T) {
    var num int
    var pointer *int = &num

    if pointer != nil && *pointer != 0 {
        t.Errorf("Expected pointer to be initialized with zero, got %d", *pointer)
    }
}

// TestPointerAssignment demonstrates pointer assignment and validates the assigned values.
func TestPointerAssignment(t *testing.T) {
    var x, y int
    var pointerX *int = &x
    var pointerY *int = &y

    *pointerX = 5
    *pointerY = 10

    if pointerX != nil && pointerY != nil && x != 5 && y != 10 {
        t.Errorf("Expected x to be 5 and y to be 10, got x=%d, y=%d", x, y)
    }
}

// TestPointerDereferencing shows how to dereference pointers and compares the result.
func TestPointerDereferencing(t *testing.T) {
    var num int = 42
    var pointer *int = &num

    if pointer != nil {
        result := *pointer

        if result != 42 {
            t.Errorf("Expected dereferencing pointer to return 42, got %d", result)
        }
    } else {
        t.Errorf("Unexpected nil pointer")
    }
}

// TestPointerToStruct demonstrates using pointers with structs and updating values through pointers.
func TestPointerToStruct(t *testing.T) {
    person := Person{Name: "John", Age: 30}
    var pointer *Person = &person

    if pointer != nil {
        pointer.Age = 31

        if person.Age != 31 {
            t.Errorf("Expected age to be updated through pointer, got %d", person.Age)
        }
    } else {
        t.Errorf("Unexpected nil pointer")
    }
}

// squareByReference is a helper function for TestPointerAsFunctionParameter, squaring the value through a pointer.
func squareByReference(num *int) {
    if num != nil {
        *num = *num * *num
    }
}

// TestPointerAsFunctionParameter demonstrates using pointers as function parameters.
func TestPointerAsFunctionParameter(t *testing.T) {
    value := 5
    var pointer *int = &value

    if pointer != nil {
        squareByReference(pointer)

        if value != 25 {
            t.Errorf("Expected value to be squared to 25, got %d", value)
        }
    } else {
        t.Errorf("Unexpected nil pointer")
    }
}
