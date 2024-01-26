package samples

import (
	"errors"
	"testing"
)

// DivisionError is a custom error type for division-related errors.
type DivisionError struct {
	Divisor   int
	ErrString string
}

// Error implements the error interface for DivisionError.
func (de DivisionError) Error() string {
	return de.ErrString
}

// Divide performs division and returns the result or a DivisionError if the divisor is zero.
func DivideWithErr(dividend, divisor int) (int, error) {
	if divisor == 0 {
		return 0, DivisionError{Divisor: divisor, ErrString: "division by zero"}
	}
	return dividend / divisor, nil
}

// TestDivisionError tests error handling for division by zero.
func TestDivisionError(t *testing.T) {
	// Test division by zero
	result, err := DivideWithErr(10, 0)
	if err == nil {
		t.Error("Expected an error, but got nil")
	} else if _, ok := err.(DivisionError); !ok {
		t.Errorf("Expected a DivisionError, but got %T", err)
	}
	if result != 0 {
		t.Errorf("Expected result to be 0, but got %d", result)
	}

	// Test successful division
	result, err = DivideWithErr(20, 4)
	if err != nil {
		t.Errorf("Unexpected error: %v", err)
	}
	if result != 5 {
		t.Errorf("Expected result to be 5, but got %d", result)
	}
}

// ReadFile reads a file and returns its content or an error.
func ReadFile(filename string) (string, error) {
	if filename == "" {
		return "", errors.New("empty filename")
	}
	// Simulate file reading
	return "File content", nil
}

// TestReadFileError tests error handling for an empty filename.
func TestReadFileError(t *testing.T) {
	// Test with empty filename
	content, err := ReadFile("")
	if err == nil {
		t.Error("Expected an error, but got nil")
	} else if err.Error() != "empty filename" {
		t.Errorf("Expected 'empty filename' error, but got %v", err)
	}
	if content != "" {
		t.Errorf("Expected content to be empty, but got %s", content)
	}

	// Test successful file reading
	content, err = ReadFile("example.txt")
	if err != nil {
		t.Errorf("Unexpected error: %v", err)
	}
	if content != "File content" {
		t.Errorf("Expected content to be 'File content', but got %s", content)
	}
}

// CustomError is a custom error type for demonstrating type assertion in error handling.
type CustomError struct {
	Message string
}

// Error implements the error interface for CustomError.
func (ce CustomError) Error() string {
	return ce.Message
}

// ProcessError performs an operation that may return a CustomError.
func ProcessError() error {
	// Simulate an operation that returns a CustomError
	return CustomError{Message: "custom error"}
}

// TestTypeAssertionError tests type assertion in error handling.
func TestTypeAssertionError(t *testing.T) {
	err := ProcessError()

	// Test type assertion
	if _, ok := err.(CustomError); !ok {
		t.Errorf("Expected a CustomError, but got %T", err)
	}
}

// CustomPanic is a custom panic type for demonstrating recover in error handling.
type CustomPanic struct {
	Message string
}

// TestRecoverError tests error handling with recover.
func TestRecoverError(t *testing.T) {
	defer func() {
		if r := recover(); r != nil {
			if e, ok := r.(CustomPanic); ok {
				t.Logf("Recovered from panic: %s", e.Message)
			} else {
				t.Errorf("Unexpected panic: %v", r)
			}
		}
	}()

	// Simulate a panic
	panic(CustomPanic{Message: "custom panic"})
}

// TestErrorIs tests the use of errors.Is for checking specific errors.
func TestErrorIs(t *testing.T) {
	_, err := DivideWithErr(10, 0)

	// Use errors.Is to check for a specific error type
	if !errors.Is(err, DivisionError{Divisor: 0, ErrString: "division by zero"}) {
		t.Error("Expected to find the specific error type")
	}

	// Check specific properties of the error
	if e, ok := err.(DivisionError); ok {
		if e.Divisor != 0 {
			t.Errorf("Expected Divisor to be 0, but got %d", e.Divisor)
		}
	} else {
		t.Error("Expected to find the specific error type")
	}
}
