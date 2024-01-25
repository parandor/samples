package samples

import "testing"

// Summary: Go Pointers Usage
//
// This Go file contains sample unit tests showcasing various aspects of pointers in the Go language.
// Pointers are used in Go for referencing and manipulating memory, allowing efficient and flexible
// programming. The tests cover basic to advanced scenarios, including pointer initialization, assignment,
// dereferencing, working with structs, using pointers as function parameters, and a complex usage example
// involving a linked list.

type Node struct {
    Value int
    Next  *Node
}

func TestPointerInitialization(t *testing.T) {
    var num int
    var pointer *int = &num

    if pointer != nil && *pointer != 0 {
        t.Errorf("Expected pointer to be initialized with zero, got %d", *pointer)
    }
}

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

func squareByReference(num *int) {
    if num != nil {
        *num = *num * *num
    }
}

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

// TestComplexPointerUsage demonstrates a complex usage of pointers by implementing a linked list.
func TestComplexPointerUsage(t *testing.T) {
    // Creating a linked list: 1 -> 2 -> 3 -> 4 -> 5
    head := &Node{Value: 1}
    current := head

    for i := 2; i <= 5; i++ {
        newNode := &Node{Value: i}
        current.Next = newNode
        current = newNode
    }

    // Traversing the linked list and verifying values
    expectedValues := []int{1, 2, 3, 4, 5}
    current = head

    for i := 0; i < len(expectedValues); i++ {
        if current == nil || current.Value != expectedValues[i] {
            t.Errorf("Expected value in linked list at index %d to be %d, got %d", i, expectedValues[i], current.Value)
        }

        current = current.Next
    }
}
