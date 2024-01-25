package samples

import "testing"

// Summary: Go Slices Usage
//
// This Go file contains sample unit tests showcasing various aspects of slices in the Go language.
// Slices provide a flexible and powerful way to work with sequences of elements. The tests cover
// slice creation, appending elements, slicing, range iteration, handling nil slices, and a complex
// usage example involving filtering, sorting, and mapping.

func TestSliceCreation(t *testing.T) {
    expected := []int{1, 2, 3}
    slice := []int{1, 2, 3}

    if len(slice) != len(expected) {
        t.Errorf("Expected slice length to be %d, got %d", len(expected), len(slice))
    }

    for i, value := range slice {
        if value != expected[i] {
            t.Errorf("Expected value at index %d to be %d, got %d", i, expected[i], value)
        }
    }
}

func TestSliceAppending(t *testing.T) {
    original := []int{1, 2, 3}
    appended := append(original, 4, 5)

    expectedOriginal := []int{1, 2, 3}
    expectedAppended := []int{1, 2, 3, 4, 5}

    if len(original) != len(expectedOriginal) {
        t.Errorf("Expected original slice length to be %d, got %d", len(expectedOriginal), len(original))
    }

    if len(appended) != len(expectedAppended) {
        t.Errorf("Expected appended slice length to be %d, got %d", len(expectedAppended), len(appended))
    }

    for i, value := range original {
        if value != expectedOriginal[i] {
            t.Errorf("Expected value in original slice at index %d to be %d, got %d", i, expectedOriginal[i], value)
        }
    }

    for i, value := range appended {
        if value != expectedAppended[i] {
            t.Errorf("Expected value in appended slice at index %d to be %d, got %d", i, expectedAppended[i], value)
        }
    }
}

func TestSliceSlicing(t *testing.T) {
    original := []int{1, 2, 3, 4, 5}
    sliced := original[1:4] // Slice from index 1 to 3 (exclusive)

    expectedSliced := []int{2, 3, 4}

    if len(sliced) != len(expectedSliced) {
        t.Errorf("Expected sliced slice length to be %d, got %d", len(expectedSliced), len(sliced))
    }

    for i, value := range sliced {
        if value != expectedSliced[i] {
            t.Errorf("Expected value in sliced slice at index %d to be %d, got %d", i, expectedSliced[i], value)
        }
    }
}

func TestSliceRangeIteration(t *testing.T) {
    numbers := []int{1, 2, 3, 4, 5}
    sum := 0

    for _, value := range numbers {
        sum += value
    }

    expectedSum := 15

    if sum != expectedSum {
        t.Errorf("Expected sum of numbers to be %d, got %d", expectedSum, sum)
    }
}

func TestNilSliceHandling(t *testing.T) {
    var nilSlice []int

    nilSlice = append(nilSlice, 1, 2, 3)

    expected := []int{1, 2, 3}

    if len(nilSlice) != len(expected) {
        t.Errorf("Expected nil slice length to be %d, got %d", len(expected), len(nilSlice))
    }

    for i, value := range nilSlice {
        if value != expected[i] {
            t.Errorf("Expected value in nil slice at index %d to be %d, got %d", i, expected[i], value)
        }
    }
}

func TestComplexSliceUsage(t *testing.T) {
    numbers := []int{5, 2, 8, 1, 7, 3, 9, 4, 6}

    // Filter even numbers
    filtered := filterSlice(numbers, func(num int) bool {
        return num%2 == 0
    })

    // Sort the filtered slice in ascending order
    sortSlice(filtered)

    expectedFiltered := []int{2, 4, 6, 8}

    if len(filtered) != len(expectedFiltered) {
        t.Errorf("Expected filtered slice length to be %d, got %d", len(expectedFiltered), len(filtered))
    }

    for i, value := range filtered {
        if value != expectedFiltered[i] {
            t.Errorf("Expected value in filtered slice at index %d to be %d, got %d", i, expectedFiltered[i], value)
        }
    }
}

// filterSlice is a helper function that filters elements in a slice based on a given condition.
func filterSlice(input []int, condition func(int) bool) []int {
    var result []int

    for _, value := range input {
        if condition(value) {
            result = append(result, value)
        }
    }

    return result
}

// sortSlice is a helper function that sorts a slice in ascending order.
func sortSlice(slice []int) {
    if len(slice) > 1 {
        for i := range slice {
            minIndex := i
            for j := i + 1; j < len(slice); j++ {
                if slice[j] < slice[minIndex] {
                    minIndex = j
                }
            }
            slice[i], slice[minIndex] = slice[minIndex], slice[i]
        }
    }
}
