package samples

import (
	"testing"
)

// TestMapCreation tests the creation of a basic map.
func TestMapCreation(t *testing.T) {
	myMap := make(map[string]int)

	// Adding key-value pairs
	myMap["one"] = 1
	myMap["two"] = 2
	myMap["three"] = 3

	// Asserting the length of the map
	if len(myMap) != 3 {
		t.Errorf("Expected map length of 3, but got %d", len(myMap))
	}

	// Asserting the values of specific keys
	if myMap["one"] != 1 {
		t.Errorf("Expected value 1 for key 'one', but got %d", myMap["one"])
	}
}

// TestMapIteration tests iterating over a map using a for loop.
func TestMapIteration(t *testing.T) {
	myMap := map[string]string{
		"apple":  "red",
		"banana": "yellow",
		"grape":  "purple",
	}

	// Iterating over the map
	for key, value := range myMap {
		t.Logf("%s is %s", key, value)
	}
}

// TestMapDeletion tests deleting a key from a map.
func TestMapDeletion(t *testing.T) {
	myMap := map[string]int{
		"one":   1,
		"two":   2,
		"three": 3,
	}

	// Deleting a key from the map
	delete(myMap, "two")

	// Asserting the length of the map
	if len(myMap) != 2 {
		t.Errorf("Expected map length of 2 after deletion, but got %d", len(myMap))
	}
}

// TestMapEquality tests the equality of maps.
func TestMapEquality(t *testing.T) {
	map1 := map[string]int{"one": 1, "two": 2, "three": 3}
	map2 := map[string]int{"one": 1, "two": 2, "three": 3}

	// Asserting equality
	if !mapsAreEqual(map1, map2) {
		t.Error("Expected maps to be equal, but they are not.")
	}
}

// TestMapAdvancedUsage showcases an advanced example of using maps.
func TestMapAdvancedUsage(t *testing.T) {
	// Mapping a function to each element in a slice
	names := []string{"Alice", "Bob", "Charlie"}
	lengths := mapStrings(names, func(s string) int {
		return len(s)
	})

	// Asserting the result
	expectedLengths := map[string]int{"Alice": 5, "Bob": 3, "Charlie": 7}
	if !mapsAreEqual(lengths, expectedLengths) {
		t.Error("Expected mapped lengths to match, but they do not.")
	}
}

// Utility function to check if two maps are equal.
func mapsAreEqual(a, b map[string]int) bool {
	if len(a) != len(b) {
		return false
	}
	for key, valueA := range a {
		if valueB, ok := b[key]; !ok || valueA != valueB {
			return false
		}
	}
	return true
}

// Utility function to map a function to each element in a slice.
func mapStrings(slice []string, f func(string) int) map[string]int {
	result := make(map[string]int, len(slice))
	for _, s := range slice {
		result[s] = f(s)
	}
	return result
}
