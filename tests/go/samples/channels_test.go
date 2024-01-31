package samples

import (
	"fmt"
	"sync"
	"testing"
	"time"
)

// TestSimpleChannelCommunication demonstrates basic channel communication.
func TestSimpleChannelCommunication(t *testing.T) {
	ch := make(chan int)

	go func() {
		ch <- 42
	}()

	result := <-ch

	// Actual vs Expected
	if result != 42 {
		t.Errorf("Expected 42, got %d", result)
	}
}

// TestBufferedChannels demonstrates the use of buffered channels.
func TestBufferedChannels(t *testing.T) {
	ch := make(chan string, 3)

	go func() {
		ch <- "one"
		ch <- "two"
		ch <- "three"
	}()

	result1 := <-ch
	result2 := <-ch
	result3 := <-ch

	// Actual vs Expected
	if result1 != "one" || result2 != "two" || result3 != "three" {
		t.Errorf("Expected 'one', 'two', 'three', got %s, %s, %s", result1, result2, result3)
	}
}

// TestSelectStatement demonstrates the use of the select statement with channels.
func TestSelectStatement(t *testing.T) {
	ch1 := make(chan string)
	ch2 := make(chan int)

	go func() {
		time.Sleep(100 * time.Millisecond)
		ch1 <- "Hello"
	}()

	go func() {
		time.Sleep(200 * time.Millisecond)
		ch2 <- 42
	}()

	select {
	case msg := <-ch1:
		// Actual vs Expected
		if msg != "Hello" {
			t.Errorf("Expected 'Hello', got %s", msg)
		}
	case value := <-ch2:
		// Actual vs Expected
		if value != 42 {
			t.Errorf("Expected 42, got %d", value)
		}
	}
}

// TestWorkerPool demonstrates a simple worker pool using channels.
func TestWorkerPool(t *testing.T) {
	tasks := []string{"task1", "task2", "task3", "task4", "task5"}
	results := make(chan string, len(tasks))

	// Start worker goroutines
	for i := 1; i <= 3; i++ {
		go func(workerID int) {
			for j, task := range tasks {
				// Ensure that each task is processed by only one worker
				if j%3 == workerID-1 {
					// Simulate some processing time
					time.Sleep(5 * time.Millisecond)
					results <- fmt.Sprintf("Worker %d processed %s", workerID, task)
				}
			}
		}(i)
	}

	// Close the results channel when all workers are done
	go func() {
		time.Sleep(300 * time.Millisecond)
		close(results)
	}()

	// Collect and verify results
	var processedTasks []string
	for result := range results {
		processedTasks = append(processedTasks, result)
	}

	// Actual vs Expected
	if len(processedTasks) != len(tasks) {
		t.Errorf("Expected %d processed tasks, got %d", len(tasks), len(processedTasks))
	}
}

// TestFanOutFanIn demonstrates fan-out and fan-in using channels.
func TestFanOutFanIn(t *testing.T) {
	input := make(chan int)
	output := make(chan int)

	var wg sync.WaitGroup

	// Fan-out: Distribute tasks to multiple workers
	for i := 0; i < 3; i++ {
		wg.Add(1)
		go func(workerID int) {
			defer wg.Done()
			for task := range input {
				// Simulate some processing time
				time.Sleep(50 * time.Millisecond)
				output <- task * 2
			}
		}(i)
	}

	// Fan-in: Collect results from multiple workers
	go func() {
		for i := 1; i <= 3; i++ {
			input <- i
		}
		close(input) // Close input channel after sending all tasks
		wg.Wait()    // Wait for all fan-out goroutines to complete before closing output
		close(output)
	}()

	// Verify results
	// Actual vs Expected
	var found2, found4, found6 bool
	for result := range output {
		// Check if the result is 2, 4, or 6
		switch result {
		case 2:
			found2 = true
		case 4:
			found4 = true
		case 6:
			found6 = true
		}
	}

	// Check if at least one of 2, 4, and 6 was found in results
	if !found2 || !found4 || !found6 {
		t.Errorf("Expected at least one occurrence of each of [2, 4, 6] in results")
	}
}
