package samples

import (
	"fmt"
	"testing"
)

// Function to test: integerOperations
func integerOperations(a, b int) (sum, product, quotient int) {
	sum = a + b
	product = a * b
	quotient = a / b
	return
}

// Function to test: floatOperations
func floatOperations(x, y float64) (sum, product float64) {
	sum = x + y
	product = x * y
	return
}

// Function to test: stringConcatenation
func stringConcatenation(firstName, lastName string) string {
	return fmt.Sprintf("%s %s", firstName, lastName)
}

// Function to test: booleanOperations
func booleanOperations(p, q bool) (andResult, orResult bool) {
	andResult = p && q
	orResult = p || q
	return
}

// Function to test: zeroValues
func zeroValues() (intZero int, floatZero float64, stringZero string, boolZero bool) {
	return
}

// Test for integerOperations
func TestIntegerOperations(t *testing.T) {
	sum, product, quotient := integerOperations(10, 5)
	if sum != 15 {
		t.Errorf("Expected sum of 15, got %d", sum)
	}

	if product != 50 {
		t.Errorf("Expected product of 50, got %d", product)
	}

	if quotient != 2 {
		t.Errorf("Expected quotient of 2, got %d", quotient)
	}
}

// Test for floatOperations
func TestFloatOperations(t *testing.T) {
	sum, product := floatOperations(3.5, 2.0)
	if sum != 5.5 {
		t.Errorf("Expected sum of 5.5, got %f", sum)
	}

	if product != 7.0 {
		t.Errorf("Expected product of 7.0, got %f", product)
	}
}

// Test for stringConcatenation
func TestStringConcatenation(t *testing.T) {
	result := stringConcatenation("John", "Doe")
	if result != "John Doe" {
		t.Errorf("Expected 'John Doe', got %s", result)
	}
}

// Test for booleanOperations
func TestBooleanOperations(t *testing.T) {
	andResult, orResult := booleanOperations(true, false)
	if andResult { // != false
		t.Errorf("Expected AND result of false, got %t", andResult)
	}

	if !orResult { // != true
		t.Errorf("Expected OR result of true, got %t", orResult)
	}
}

// Test for zeroValues
func TestZeroValues(t *testing.T) {
	intZero, floatZero, stringZero, boolZero := zeroValues()
	if intZero != 0 {
		t.Errorf("Expected zero value for int, got %d", intZero)
	}

	if floatZero != 0.0 {
		t.Errorf("Expected zero value for float, got %f", floatZero)
	}

	if stringZero != "" {
		t.Errorf("Expected zero value for string, got %s", stringZero)
	}

	if boolZero { // != false 
		t.Errorf("Expected zero value for bool, got %t", boolZero)
	}
}
