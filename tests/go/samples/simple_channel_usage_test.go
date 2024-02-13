package samples

import (
    "testing"
)

// TestSendReceiveOnChannel tests sending and receiving a value on a channel.
func TestSendReceiveOnChannel(t *testing.T) {
    ch := make(chan int)
    go func() {
        ch <- 42
    }()
    val := <-ch
    if val != 42 {
        t.Errorf("Expected value 42, got %d", val)
    }
}

// TestSimpleChannelBufferedChannel tests using a buffered channel.
func TestSimpleChannelBufferedChannel(t *testing.T) {
    ch := make(chan int, 2)
    ch <- 1
    ch <- 2
    select {
    case ch <- 3: // Try to send another value to a buffered channel, this should block
        t.Error("Sending to buffered channel should block")
    default:
        // Sending should block as the channel is full, which is the expected behavior
    }
}

// TestClosingChannel tests closing a channel and receiving from a closed channel.
func TestClosingChannel(t *testing.T) {
    ch := make(chan int)
    close(ch)
    _, ok := <-ch
    if ok {
        t.Error("Received from a closed channel")
    }
}

// TestSimpleChannelSelectStatement tests using the select statement with channels.
func TestSimpleChannelSelectStatement(t *testing.T) {
    ch1 := make(chan int)
    ch2 := make(chan int)

    go func() {
        ch1 <- 1
    }()
    go func() {
        ch2 <- 2
    }()

    select {
    case val := <-ch1:
        if val != 1 {
            t.Errorf("Expected value 1 from ch1, got %d", val)
        }
    case val := <-ch2:
        if val != 2 {
            t.Errorf("Expected value 2 from ch2, got %d", val)
        }
    }
}

// TestSelectWithDefault tests using the select statement with a default case.
func TestSelectWithDefault(t *testing.T) {
    ch := make(chan int)

    select {
    case <-ch:
        t.Error("Received from an empty channel")
    default:
        // No value received, which is the expected behavior
    }
}
