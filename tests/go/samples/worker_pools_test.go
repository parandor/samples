package samples

import (
	//"fmt"
	"sync"
	"testing"
)

// Worker represents a worker that executes tasks.
type Worker struct {
	// ID: This field represents the identifier of the worker.
	// It's a simple integer value used to uniquely identify each worker in the pool.
	ID int
	// TaskStream: This field is a receive-only channel (<-chan) of integers.
	// It's used to receive tasks that need to be processed by the worker.
	// The worker listens on this channel for incoming tasks.
	TaskStream <-chan int
	// Result: This field is a send-only channel (chan<-) of integers.
	// It's used by the worker to send the results of processed tasks back to
	// the main program or another component that's interested in the results.
	Result chan<- int
}

// Start starts the worker to listen for tasks and process them.
func (w *Worker) Start() {
	for task := range w.TaskStream {
		// Perform some task processing (for simplicity, just doubling the input)
		result := task * 2
		// Send the result to the result channel
		w.Result <- result
	}
}

// TestWorkerPoolSimple tests a simple worker pool with one worker.
func TestWorkerPoolSimple(t *testing.T) {
	taskStream := make(chan int)
	resultStream := make(chan int)

	// Create a worker pool with one worker
	worker := Worker{ID: 1, TaskStream: taskStream, Result: resultStream}
	go worker.Start()

	// Send a task to the worker pool
	taskStream <- 5

	// Receive the result from the worker pool
	result := <-resultStream

	// Verify the result
	if result != 10 {
		t.Errorf("Expected result 10, got %d", result)
	}
}

// TestWorkerPoolMultipleWorkers tests a worker pool with multiple workers.
func TestWorkerPoolMultipleWorkers(t *testing.T) {
	numWorkers := 3
	taskStream := make(chan int)
	resultStream := make(chan int)

	// Create multiple workers and start them
	var wg sync.WaitGroup
	for i := 0; i < numWorkers; i++ {
		wg.Add(1)
		worker := Worker{ID: i + 1, TaskStream: taskStream, Result: resultStream}
		go func() {
			defer wg.Done()
			worker.Start()
		}()
	}

	// Create a separate wait group for waiting until all results are sent
	var resultWG sync.WaitGroup
	resultWG.Add(numWorkers)

	// Send tasks to the worker pool
	go func() {
		tasks := []int{1, 8, 27}
		for _, task := range tasks {
			taskStream <- task
		}
		close(taskStream)
	}()

	// Receive results from the worker pool
	go func() {
		receivedResults := make(map[int]int) // Map to store received results
	
		for i := 0; i < numWorkers; i++ {
			result := <-resultStream
			receivedResults[result] = result // Store the received result
		}

		// Check the received results against the expected values
		tasks := []int{1, 8, 27}
		for _, item := range(tasks) {
			expected := item * 2 // Each task doubled by the worker
			if result, ok := receivedResults[expected]; !ok {
				// Result not received for the expected value
				t.Errorf("Result missing for expected value %d", expected)
			} else if result != expected {
				// Received result does not match the expected value
				t.Errorf("Expected result %d, got %d", expected, result)
			}
			resultWG.Done()
		}
	}()

	// Wait for all workers to finish sending results
	resultWG.Wait()

	// Close the result stream
	close(resultStream)
}

// TestWorkerPoolWithWorkerShutdown tests a worker pool with workers that can be shutdown gracefully.
func TestWorkerPoolWithWorkerShutdown(t *testing.T) {
	taskStream := make(chan int)
	resultStream := make(chan int)

	// Create a function to start a worker
	startWorker := func(id int) {
		worker := Worker{ID: id, TaskStream: taskStream, Result: resultStream}
		go worker.Start()
	}

	var wg sync.WaitGroup

	// Start with three workers
	startWorker(1)
	startWorker(2)
	startWorker(3)

	// Send tasks to the worker pool
	tasks := []int{2, 4, 6}
	for _, task := range tasks {
		taskStream <- task
	}

	// Shutdown worker with ID 2
	close(taskStream)


	// Verify the results
	expectedResults := []int{4, 8, 12}
	go func() {
		for _, expected := range expectedResults {
			result := <-resultStream
			if result != expected {
				t.Errorf("Expected result %d, got %d", expected, result)
			}
		}
		wg.Done()	
		// Close the result stream
		close(resultStream)
	}()
	wg.Wait()
}
