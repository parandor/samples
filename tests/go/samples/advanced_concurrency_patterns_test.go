package samples

import (
	"sync"
	"testing"
)

// TestBasicConcurrencyPattern demonstrates a basic goroutine creation.
func TestBasicConcurrencyPattern(t *testing.T) {
	done := make(chan bool)

	go func() {
		// Perform some computation
		done <- true
	}()

	<-done
}

// TestChannelUsagePattern demonstrates a simple channel usage pattern.
func TestChannelUsagePattern(t *testing.T) {
	input := make(chan int)
	output := make(chan int)

	go func() {
		value := <-input
		output <- value * 2
	}()

	input <- 5
	result := <-output

	if result != 10 {
		t.Errorf("Expected result 10, got %d", result)
	}
}

// TestWorkerPoolPattern demonstrates a basic worker pool pattern.
func TestWorkerPoolPattern(t *testing.T) {
	const numWorkers = 3

	taskStream := make(chan int)
	resultStream := make(chan int)

	var wg sync.WaitGroup
	for i := 0; i < numWorkers; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for task := range taskStream {
				// Process task
				resultStream <- task * 2
			}
		}()
	}

	tasks := []int{1, 2, 3, 4, 5}
	go func() {
		for _, task := range tasks {
			taskStream <- task
		}
		close(taskStream)
	}()

	go func() {
		wg.Wait()
		close(resultStream)
	}()

	// Verify results
	expected := make(map[int]bool)
	for i := 0; i < len(tasks); i++ {
		expected[(i+1)*2] = true // Store expected results
	}

	var results []int
	for result := range resultStream {
		results = append(results, result)
	}

	// Check for out-of-sequence results
	for _, r := range results {
		if !expected[r] {
			t.Errorf("Unexpected result: %d", r)
		}
	}
}

// TestMutexPattern demonstrates a basic mutex pattern.
func TestMutexPattern(t *testing.T) {
	var (
		counter int
		mutex   sync.Mutex
		wg      sync.WaitGroup
	)

	const numWorkers = 5
	wg.Add(numWorkers)

	for i := 0; i < numWorkers; i++ {
		go func() {
			defer wg.Done()
			for j := 0; j < 1000; j++ {
				mutex.Lock()
				counter++
				mutex.Unlock()
			}
		}()
	}

	wg.Wait()

	if counter != numWorkers*1000 {
		t.Errorf("Counter value incorrect, expected %d, got %d", numWorkers*1000, counter)
	}
}

// TestSemaphorePattern demonstrates a simple semaphore pattern.
func TestSemaphorePattern(t *testing.T) {
	const (
		numWorkers  = 5
		maxParallel = 2
	)

	taskStream := make(chan int)
	resultStream := make(chan int)

	semaphore := make(chan struct{}, maxParallel)

	var wg sync.WaitGroup
	wg.Add(numWorkers)

	// Send tasks to the task stream
	go func() {
		defer close(taskStream)
		for i := 0; i < numWorkers; i++ {
			taskStream <- i
		}
	}()

	for i := 0; i < numWorkers; i++ {
		go func() {
			defer wg.Done()
			for task := range taskStream {
				semaphore <- struct{}{}
				// Process task
				resultStream <- task
				<-semaphore
			}
		}()
	}

	go func() {
		wg.Wait()
		close(resultStream)
	}()

	var results []int
	for result := range resultStream {
		results = append(results, result)
	}

	if len(results) != numWorkers {
		t.Errorf("Expected %d results, got %d", numWorkers, len(results))
	}
}
