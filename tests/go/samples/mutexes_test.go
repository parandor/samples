package samples

import (
	"sync"
	"testing"
)

// Counter represents a simple counter with mutex protection.
type Counter struct {
	mu    sync.Mutex
	value int
}

// Increment increments the counter by 1.
func (c *Counter) Increment() {
	c.mu.Lock()
	defer c.mu.Unlock()
	c.value++
}

// Decrement decrements the counter by 1.
func (c *Counter) Decrement() {
	c.mu.Lock()
	defer c.mu.Unlock()
	c.value--
}

// Value returns the current value of the counter.
func (c *Counter) Value() int {
	c.mu.Lock()
	defer c.mu.Unlock()
	return c.value
}

// TestCounterIncrement tests incrementing the counter.
func TestCounterIncrement(t *testing.T) {
	counter := Counter{}
	counter.Increment()
	counter.Increment()
	if counter.Value() != 2 {
		t.Errorf("Expected counter value 2, got %d", counter.Value())
	}
}

// TestCounterDecrement tests decrementing the counter.
func TestCounterDecrement(t *testing.T) {
	counter := Counter{value: 5}
	counter.Decrement()
	counter.Decrement()
	if counter.Value() != 3 {
		t.Errorf("Expected counter value 3, got %d", counter.Value())
	}
}

// TestCounterConcurrentIncrement tests concurrent incrementing of the counter.
func TestCounterConcurrentIncrement(t *testing.T) {
	counter := Counter{}
	var wg sync.WaitGroup
	for i := 0; i < 1000; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			counter.Increment()
		}()
	}
	wg.Wait()
	if counter.Value() != 1000 {
		t.Errorf("Expected counter value 1000, got %d", counter.Value())
	}
}

// TestCounterConcurrentIncrementDecrement tests concurrent incrementing and decrementing of the counter.
func TestCounterConcurrentIncrementDecrement(t *testing.T) {
	counter := Counter{}
	var wg sync.WaitGroup
	for i := 0; i < 500; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			counter.Increment()
		}()
		wg.Add(1)
		go func() {
			defer wg.Done()
			counter.Decrement()
		}()
	}
	wg.Wait()
	if counter.Value() != 0 {
		t.Errorf("Expected counter value 0, got %d", counter.Value())
	}
}

// TestCounterConcurrentReadWrite tests concurrent read and write operations on the counter.
func TestCounterConcurrentReadWrite(t *testing.T) {
	counter := Counter{}
	var wg sync.WaitGroup
	// Start 1000 goroutines to increment the counter
	for i := 0; i < 1000; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			counter.Increment()
		}()
	}
	// Start 1000 goroutines to read the counter value
	for i := 0; i < 1000; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			_ = counter.Value()
		}()
	}
	wg.Wait()
	// Check if the final value of the counter is 1000
	if counter.Value() != 1000 {
		t.Errorf("Expected counter value 1000, got %d", counter.Value())
	}
}
