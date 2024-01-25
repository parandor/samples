package samples

import (
    "reflect"
    "testing"
)

// Add returns the sum of two integers.
func Add(a, b int) int {
    return a + b
}

// Sum calculates the sum of an arbitrary number of integers.
func Sum(numbers ...int) int {
    sum := 0
    for _, num := range numbers {
        sum += num
    }
    return sum
}

// Divide returns the quotient and remainder of dividing two integers.
func Divide(a, b int) (int, int) {
    quotient := a / b
    remainder := a % b
    return quotient, remainder
}

// Apply applies a given function to each element of a slice.
func Apply(nums []int, fn func(int) int) []int {
    result := make([]int, len(nums))
    for i, num := range nums {
        result[i] = fn(num)
    }
    return result
}

// SquareAll returns a new slice with each element squared.
func SquareAll(nums []int) []int {
    square := func(x int) int { return x * x }
    return Apply(nums, square)
}

func TestAdd(t *testing.T) {
    result := Add(2, 3)
    expected := 5

    if result != expected {
        t.Errorf("Add(2, 3) = %d; want %d", result, expected)
    }
}

func TestSum(t *testing.T) {
    result := Sum(1, 2, 3, 4, 5)
    expected := 15

    if result != expected {
        t.Errorf("Sum(1, 2, 3, 4, 5) = %d; want %d", result, expected)
    }
}

func TestDivide(t *testing.T) {
    quotient, remainder := Divide(10, 3)
    expectedQuotient := 3
    expectedRemainder := 1

    if quotient != expectedQuotient || remainder != expectedRemainder {
        t.Errorf("Divide(10, 3) = (%d, %d); want (%d, %d)", quotient, remainder, expectedQuotient, expectedRemainder)
    }
}

func TestApply(t *testing.T) {
    nums := []int{1, 2, 3, 4}
    double := func(x int) int { return x * 2 }
    result := Apply(nums, double)
    expected := []int{2, 4, 6, 8}

    if !reflect.DeepEqual(result, expected) {
        t.Errorf("Apply([1, 2, 3, 4], double) = %v; want %v", result, expected)
    }
}

func TestSquareAll(t *testing.T) {
    nums := []int{1, 2, 3, 4}
    result := SquareAll(nums)
    expected := []int{1, 4, 9, 16}

    if !reflect.DeepEqual(result, expected) {
        t.Errorf("SquareAll([1, 2, 3, 4]) = %v; want %v", result, expected)
    }
}
