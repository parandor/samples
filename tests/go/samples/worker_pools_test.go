package samples

import (
	"sync"
	"testing"
)

// Worker represents a worker that executes tasks.
type Worker struct {
	// ID: This field represents the identifier of the worker. 
	// It's a simple integer value used to uniquely identify each worker in the pool.
	ID         int
	// TaskStream: This field is a receive-only channel (<-chan) of integers. 
	// It's used to receive tasks that need to be processed by the worker. 
	// The worker listens on this channel for incoming tasks.
	TaskStream <-chan int
	// Result: This field is a send-only channel (chan<-) of integers. 
	// It's used by the worker to send the results of processed tasks back to 
	// the main program or another component that's interested in the results.
	Result     chan<- int
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

	// Send tasks to the worker pool
	tasks := []int{3, 7, 11}
	for _, task := range tasks {
		taskStream <- task
	}

	// Close the task stream to signal the workers to stop
	close(taskStream)

	// Wait for all workers to finish
	wg.Wait()

	// Close the result stream
	close(resultStream)

	// Verify the results
	expectedResults := []int{6, 14, 22}
	for _, expected := range expectedResults {
		result := <-resultStream
		if result != expected {
			t.Errorf("Expected result %d, got %d", expected, result)
		}
	}
}

// TestWorkerPoolDynamicWorkers tests a worker pool with dynamically changing number of workers.
func TestWorkerPoolDynamicWorkers(t *testing.T) {
	taskStream := make(chan int)
	resultStream := make(chan int)

	// Create a function to start a worker
	startWorker := func(id int) {
		worker := Worker{ID: id, TaskStream: taskStream, Result: resultStream}
		go worker.Start()
	}

	// Start with two workers
	startWorker(1)
	startWorker(2)

	// Send tasks to the worker pool
	tasks := []int{2, 4, 6}
	for _, task := range tasks {
		taskStream <- task
	}

	// Close the task stream to signal the workers to stop
	close(taskStream)

	// Close the result stream
	close(resultStream)

	// Verify the results
	expectedResults := []int{4, 8, 12}
	for _, expected := range expectedResults {
		result := <-resultStream
		if result != expected {
			t.Errorf("Expected result %d, got %d", expected, result)
		}
	}
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

	// Close the result stream
	close(resultStream)

	// Verify the results
	expectedResults := []int{4, 8, 12}
	for _, expected := range expectedResults {
		result := <-resultStream
		if result != expected {
			t.Errorf("Expected result %d, got %d", expected, result)
		}
	}
}
