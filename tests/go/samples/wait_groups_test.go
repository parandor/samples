package samples

import (
	"context"
	"sync"
	"testing"
	"time"

	"github.com/stretchr/testify/assert"
)

// Wait Groups and Concurrency
// 
// Template:
//
// var wg sync.WaitGroup
// concurrency := 1000
// for i := 0; i < concurrency; i++ {  // 1. start loop
// 	wg.Add(1)                          // 2. wait flag
// 	go func() {                        // 3. goroutine
// 		defer wg.Done()                // 4. defer wait group Done to unset wait flag
// 		                               // 5. Call to execute concurrently
// 	}()                                // 6. Close goroutine
// }                                   // 7. Close loop
// wg.Wait()                           // 8. Wait until work finishes

// Beginner level: Test for basic usage of WaitGroup.
func TestWaitGroupBasic(t *testing.T) {
	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		defer wg.Done()
		// Simulate some work
	}()

	wg.Wait()
	// At this point, the wait group has waited for the goroutine to finish.
	assert.True(t, true, "Basic WaitGroup test passed")
}

// Beginner level: Test for waiting for multiple goroutines with WaitGroup.
func TestWaitGroupMultipleGoroutines(t *testing.T) {
	var wg sync.WaitGroup
	numGoroutines := 5
	wg.Add(numGoroutines)

	for i := 0; i < numGoroutines; i++ {
		go func(id int) {
			defer wg.Done()
			// Simulate some work
		}(i)
	}

	wg.Wait()
	// At this point, all the goroutines have finished their work.
	assert.True(t, true, "Multiple goroutines WaitGroup test passed")
}

// Intermediate level: Test for using WaitGroup with nested goroutines.
func TestWaitGroupNestedGoroutines(t *testing.T) {
	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		defer wg.Done()
		// Spawn another goroutine
		wg.Add(1)
		go func() {
			defer wg.Done()
			// Simulate some work
		}()
	}()

	wg.Wait()
	// At this point, both the outer and inner goroutines have finished their work.
	assert.True(t, true, "Nested goroutines WaitGroup test passed")
}

// Intermediate level: Test for using WaitGroup with error handling.
func TestWaitGroupWithErrorHandling(t *testing.T) {
	var wg sync.WaitGroup
	numGoroutines := 5
	wg.Add(numGoroutines)

	errCh := make(chan error, numGoroutines)

	for i := 0; i < numGoroutines; i++ {
		go func(id int) {
			defer wg.Done()
			// Simulate some work
			// If an error occurs, send it to the error channel
			// errCh <- someError
		}(i)
	}

	go func() {
		wg.Wait()
		close(errCh)
	}()

	for err := range errCh {
		assert.NoError(t, err, "Error occurred")
	}
}

// Advanced level: Test for using WaitGroup with context cancellation.
func TestWaitGroupWithContextCancellation(t *testing.T) {
	// Create a context with cancellation.
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	// Create a WaitGroup.
	var wg sync.WaitGroup

	// Add some goroutines to the WaitGroup.
	numGoroutines := 3
	wg.Add(numGoroutines)

	// Start goroutines that simulate work.
	for i := 0; i < numGoroutines; i++ {
		go func(id int) {
			defer wg.Done()
			select {
			// Simulate some work that can be canceled if the context is canceled.
			case <-time.After(time.Second):
				// Simulated work done.
			case <-ctx.Done():
				// If context is canceled, return immediately.
				return
			}
		}(i)
	}

	// Start a goroutine to cancel the context after a certain duration.
	go func() {
		time.Sleep(500 * time.Millisecond) // Wait for some time before canceling.
		cancel()                            // Cancel the context.
	}()

	// Wait for all goroutines to finish or for the context to be canceled.
	wg.Wait()

	// Assert that the context has been canceled.
	assert.True(t, ctx.Err() != nil, "Context cancellation WaitGroup test passed")
}