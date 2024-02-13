package samples

import (
    "testing"
    "time"
)

// TestBasicGoroutine just starts a basic goroutine.
func TestBasicGoroutine(t *testing.T) {
    go func() {
        // Goroutine does nothing
    }()
    // No assertion needed, just ensure the test runs without error.
}

// TestGoroutineWithSleep starts a goroutine that sleeps for a short duration.
func TestGoroutineWithSleep(t *testing.T) {
    done := make(chan bool)
    go func() {
        time.Sleep(100 * time.Millisecond)
        done <- true
    }()
    select {
    case <-done:
        // Goroutine completed its task
    case <-time.After(200 * time.Millisecond):
        t.Error("Goroutine took too long to complete")
    }
}

// TestGoroutineWithChannel creates a goroutine that communicates with a channel.
func TestGoroutineWithChannel(t *testing.T) {
    ch := make(chan int)
    go func() {
        ch <- 42
    }()
    val := <-ch
    if val != 42 {
        t.Errorf("Expected value 42, got %d", val)
    }
}

// TestGoroutineWithParameter starts a goroutine that takes a parameter.
func TestGoroutineWithParameter(t *testing.T) {
    param := "Hello, goroutine!"
    done := make(chan bool)
    go func(s string) {
        t.Log(s)
        done <- true
    }(param)
    <-done
    // Ensure the goroutine completes its task before finishing the test
}

// TestBasicMultipleGoroutines starts multiple goroutines concurrently.
func TestBasicMultipleGoroutines(t *testing.T) {
    numGoroutines := 5
    done := make(chan bool, numGoroutines)
    for i := 0; i < numGoroutines; i++ {
        go func(id int) {
            t.Logf("Goroutine %d", id)
            done <- true
        }(i)
    }
    for i := 0; i < numGoroutines; i++ {
        <-done
    }
}
