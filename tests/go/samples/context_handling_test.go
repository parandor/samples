package samples

import (
	"context"
	"fmt"
	"sync"
	"testing"
	"time"
)

// Context is a package for carrying deadlines, cancellation signals, and other request-scoped
// values across API boundaries and between processes.
// It is typically used to manage cancellation signals, deadlines, and request-scoped values
// across different goroutines and functions in Go programs.
// Context is commonly used in concurrent and networked Go programs to handle timeouts,
// cancelation, and passing data across multiple goroutines.
// It provides a way to propagate deadlines, cancelation signals, and request-scoped values
// through the call stack of goroutines without the need to pass them explicitly as function
// parameters.
// Context is often used with goroutines, HTTP servers, and other asynchronous operations in
// Go to manage the lifecycle of operations and ensure proper cleanup.
// For example, it can be used to cancel a long-running operation if a client disconnects or
// to set a timeout for an HTTP request.
// Context should be passed explicitly to functions and goroutines that need access to its
// values or cancellation signals, rather than relying on global state or shared variables.
// It is important to properly handle context cancellation and deadlines in Go programs to
// avoid resource leaks and ensure the responsiveness and reliability of concurrent operations.
// By using context, developers can write more robust and scalable Go programs that gracefully
// handle cancellation, timeouts, and request-scoped data propagation.

// FunctionWithContext demonstrates basic context handling.
func FunctionWithContext(ctx context.Context) {
	select {
	case <-ctx.Done():
		fmt.Println("Context canceled or expired")
	default:
		fmt.Println("Context is active")
		// Simulate some work
		time.Sleep(100 * time.Millisecond)
	}
}

// TestContextCancellationPattern demonstrates context cancellation.
func TestContextCancellationPattern(t *testing.T) {
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	go FunctionWithContext(ctx)

	// Cancel the context after a delay
	time.AfterFunc(50*time.Millisecond, cancel)
	time.Sleep(200 * time.Millisecond)

	select {
	case <-ctx.Done():
		// Ensure context is canceled
		if ctx.Err() == nil {
			t.Errorf("Expected context to be canceled, but it's active")
		}
	default:
		t.Errorf("Expected context to be canceled, but it's active")
	}
}

// TestContextTimeoutPattern demonstrates context timeout.
func TestContextTimeoutPattern(t *testing.T) {
	ctx, cancel := context.WithTimeout(context.Background(), 100*time.Millisecond)
	defer cancel()

	go FunctionWithContext(ctx)

	// Wait for context timeout
	time.Sleep(200 * time.Millisecond)

	select {
	case <-ctx.Done():
		// Ensure context is canceled due to timeout
		if ctx.Err() == nil {
			t.Errorf("Expected context to be canceled due to timeout, but it's active")
		}
	default:
		t.Errorf("Expected context to be canceled due to timeout, but it's active")
	}
}

// TestContextValuePattern demonstrates context value propagation.
func TestContextValuePattern(t *testing.T) {
	ctx := context.WithValue(context.Background(), "key", "value")

	// Pass the context to a worker function
	go func(ctx context.Context) {
		if value, ok := ctx.Value("key").(string); ok {
			if value != "value" {
				t.Errorf("Expected value 'value', got '%s'", value)
			}
		} else {
			t.Errorf("Value not found in context")
		}
	}(ctx)

	// Simulate some work
	time.Sleep(100 * time.Millisecond)
}

// TestContextDeadlinePattern demonstrates context with deadline.
func TestContextDeadlinePattern(t *testing.T) {
	ctx, cancel := context.WithDeadline(context.Background(), time.Now().Add(100*time.Millisecond))
	defer cancel()

	select {
	case <-ctx.Done():
		// Ensure context is canceled due to deadline
		if ctx.Err() == nil {
			t.Errorf("Expected context to be canceled due to deadline, but it's active")
		}
	case <-time.After(200 * time.Millisecond):
		t.Errorf("Operation timed out")
	}
}

// TestContextCancellationPropagationPattern demonstrates context cancellation propagation.
func TestContextCancellationPropagationPattern(t *testing.T) {
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	var wg sync.WaitGroup
	wg.Add(1)

	// Pass the context to a worker function
	go func(ctx context.Context) {
		defer wg.Done()
		select {
		case <-ctx.Done():
			// Ensure context is canceled
			if ctx.Err() == nil {
				t.Errorf("Expected context to be canceled, but it's active")
			}
		case <-time.After(50 * time.Millisecond):
			fmt.Println("Worker: Finished work")
		}
	}(ctx)

	// Cancel the context after a delay
	time.AfterFunc(25*time.Millisecond, cancel)
	wg.Wait()
}

func main() {}
