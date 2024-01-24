package samples

import (
	"testing"
)

// Function to test: simpleIfElse
func simpleIfElse(value int) string {
	if value > 0 {
		return "Positive"
	} else if value == 0 {
		return "Zero"
	} else {
		return "Negative"
	}
}

// Function to test: switchExample
func switchExample(day string) string {
	switch day {
	case "Monday":
		return "Start of the week"
	case "Friday", "Saturday":
		return "Weekend!"
	default:
		return "Midweek"
	}
}

// Function to test: forLoop
func forLoop(n int) int {
	sum := 0
	for i := 1; i <= n; i++ {
		sum += i
	}
	return sum
}

// Function to test: breakAndContinue
func breakAndContinue() (int, int) {
	sum := 0
	for i := 1; i <= 10; i++ {
		if i%2 == 0 {
			continue // Skip even numbers
		}
		sum += i
		if i == 5 {
			break // Stop when i is 5
		}
	}
	return sum, 5
}

// Function to test: nestedLoop
func nestedLoop(rows, cols int) [][]int {
	matrix := make([][]int, rows)
	for i := range matrix {
		matrix[i] = make([]int, cols)
		for j := range matrix[i] {
			matrix[i][j] = i*cols + j
		}
	}
	return matrix
}

// Test for simpleIfElse
func TestSimpleIfElse(t *testing.T) {
	result := simpleIfElse(5)
	if result != "Positive" {
		t.Errorf("Expected 'Positive', got %s", result)
	}

	result = simpleIfElse(0)
	if result != "Zero" {
		t.Errorf("Expected 'Zero', got %s", result)
	}

	result = simpleIfElse(-5)
	if result != "Negative" {
		t.Errorf("Expected 'Negative', got %s", result)
	}
}

// Test for switchExample
func TestSwitchExample(t *testing.T) {
	result := switchExample("Monday")
	if result != "Start of the week" {
		t.Errorf("Expected 'Start of the week', got %s", result)
	}

	result = switchExample("Friday")
	if result != "Weekend!" {
		t.Errorf("Expected 'Weekend!', got %s", result)
	}

	result = switchExample("Wednesday")
	if result != "Midweek" {
		t.Errorf("Expected 'Midweek', got %s", result)
	}
}

// Test for forLoop
func TestForLoop(t *testing.T) {
	result := forLoop(5)
	if result != 15 {
		t.Errorf("Expected 15, got %d", result)
	}

	result = forLoop(0)
	if result != 0 {
		t.Errorf("Expected 0, got %d", result)
	}
}

// Test for breakAndContinue
func TestBreakAndContinue(t *testing.T) {
	sum, stop := breakAndContinue()
	if sum != 9 {
		t.Errorf("Expected sum of 9, got %d", sum)
	}

	if stop != 5 {
		t.Errorf("Expected stop at 5, got %d", stop)
	}
}

// Test for nestedLoop
func TestNestedLoop(t *testing.T) {
	matrix := nestedLoop(2, 3)
	expected := [][]int{{0, 1, 2}, {3, 4, 5}}

	for i, row := range matrix {
		for j, value := range row {
			if value != expected[i][j] {
				t.Errorf("Expected %d, got %d at position (%d, %d)", expected[i][j], value, i, j)
			}
		}
	}
}
