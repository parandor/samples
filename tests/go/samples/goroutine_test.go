package samples

import (
	"sync"
	"testing"
	"time"
)

// In Go, the go func() statement starts a new goroutine, not a separate
// operating system thread. Goroutines are lightweight threads managed by the
// Go runtime, and they are scheduled onto multiple OS threads. The Go runtime
// multiplexes many goroutines onto a smaller number of operating system threads,
// allowing concurrent execution without the need for creating a separate OS
// thread for each goroutine.

// Goroutines are designed to be more efficient than traditional threads,
// as they have a smaller footprint and are managed by the Go runtime's scheduler,
// which can dynamically adjust the number of OS threads based on the workload.

// So, while the go func() statement does result in concurrent execution, it
// doesn't necessarily imply the creation of a new OS thread for every goroutine.
// Instead, the Go runtime efficiently schedules goroutines onto a pool of OS threads.

func TestSimpleGoroutine(t *testing.T) {
	// Simple example of a goroutine using a channel for synchronization
	done := make(chan bool)

	go func() {
		// Simulating some work
		time.Sleep(100 * time.Millisecond)
		done <- true // Signal that the goroutine has completed
	}()

	select {
	case <-done:
		// Goroutine completed successfully
	case <-time.After(200 * time.Millisecond):
		t.Error("Timeout waiting for the goroutine to complete")
	}
}

func TestMultipleGoroutines(t *testing.T) {
	// Example of using a sync.WaitGroup to wait for multiple goroutines to finish
	var wg sync.WaitGroup
	wg.Add(3) // Set the wait group counter to the number of goroutines

	for i := 0; i < 3; i++ {
		go func(id int) {
			// Simulating some work
			defer wg.Done() // Decrement the wait group counter when the goroutine completes
			t.Logf("Goroutine %d completed", id)
		}(i)
	}

	wg.Wait() // Wait until all goroutines signal completion
}

func TestChannelCommunication(t *testing.T) {
	// Example of simple channel communication between goroutines
	ch := make(chan int)

	go func() {
		// Sending data to the channel
		ch <- 42
	}()

	// Simulating some work
	time.Sleep(100 * time.Millisecond)

	// Receiving data from the channel
	result := <-ch

	if result != 42 {
		t.Errorf("Expected 42, got %d", result)
	}
}

func TestBufferedChannel(t *testing.T) {
	// Example of using a buffered channel for communication between goroutines
	ch := make(chan string, 2)

	go func() {
		// Sending data to the buffered channel
		ch <- "Hello"
		ch <- "World"
		close(ch) // Closing the channel to signal no more data will be sent
	}()

	// Simulating some work
	time.Sleep(100 * time.Millisecond)

	// Receiving data from the buffered channel
	result1 := <-ch
	result2 := <-ch

	if result1 != "Hello" || result2 != "World" {
		t.Errorf("Expected 'Hello' and 'World', got '%s' and '%s'", result1, result2)
	}
}

func TestTimeout(t *testing.T) {
	// Example of using a timeout with a select statement for goroutine synchronization
	resultCh := make(chan string)

	go func() {
		// Simulating a long-running task
		time.Sleep(100 * time.Millisecond)
		resultCh <- "Task completed"
	}()

	select {
	case result := <-resultCh:
		t.Logf("Goroutine result: %s", result)
	case <-time.After(500 * time.Millisecond):
		t.Error("Timeout waiting for the goroutine to complete")
	}
}

func TestDeferExamples(t *testing.T) {
	// Example of using defer to ensure some statements are executed at the end of the function
	// Defer statements are executed in a Last In, First Out (LIFO) order when the function exits
	defer func() {
		t.Log("Defer Example 1: Executed at the end of the function")
	}()

	// Example of using defer with an anonymous function and passing parameters
	defer func(msg string) {
		t.Logf("Defer Example 2: %s", msg)
	}("Executed with defer")

	// Rest of the test function
}
