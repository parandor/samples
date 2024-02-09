package server_test

import (
	"context"
	"net/http/httptest"
	"testing"
	"github.com/parandor/samples/internal/ticketing_system/server"

	v1 "github.com/parandor/samples/internal/gen/tests/go/samples/ticketing_system/v1"
	ticketing_systemv1connect "github.com/parandor/samples/internal/gen/tests/go/samples/ticketing_system/v1/ticketing_systemv1connect"
	connect "connectrpc.com/connect"
)

func TestTicketingSystemHandlerAndClient(t *testing.T) {
	// Create a new instance of MyTicketingServiceHandler
	_, httpHandler := server.NewMyTicketingServiceHandler()

	// Create a new HTTP server with the handler
	server := httptest.NewServer(httpHandler)
	defer server.Close()

	// Create a new TicketingSystemClient
	client := ticketing_systemv1connect.NewTicketingServiceClient(server.Client(), server.URL)

	// Test the handler methods
	testCreateTicket(t, client)
	testAddComment(t, client)
	testUpdateTicketStatus(t, client)
	testListTickets(t, client)
}

func testCreateTicket(t *testing.T, client ticketing_systemv1connect.TicketingServiceClient) {
	// Prepare a request to create a ticket


	// Call the CreateTicket method
	response, err := client.CreateTicket(context.Background(), &connect.Request[v1.CreateTicketRequest]{
		Msg: &v1.CreateTicketRequest{
			Ticket: &v1.Ticket{Id: "1", Subject: "Test Ticket", Status: "OPEN"},
		},
	})
	if err != nil {
		t.Fatalf("CreateTicket failed: %v", err)
	}

	// Check if the response contains the ticket
	if response == nil || response.Msg.Ticket == nil {
		t.Fatalf("CreateTicket response is nil or missing ticket")
	}
}

func testAddComment(t *testing.T, client ticketing_systemv1connect.TicketingServiceClient) {

	// Call the AddComment method
	response, err := client.AddComment(context.Background(), &connect.Request[v1.AddCommentRequest]{
		Msg: &v1.AddCommentRequest{
			TicketId:      "1", // Assuming ticket with ID 1 exists
			Comment:       "Test Comment",
		},
	})
	if err != nil {
		t.Fatalf("AddComment failed: %v", err)
	}

	// Check if the response contains the ticket with the added comment
	if response == nil || response.Msg.Ticket == nil || len(response.Msg.Ticket.Comments) == 0 {
		t.Fatalf("AddComment response is nil or missing ticket comment")
	}
}

func testUpdateTicketStatus(t *testing.T, client ticketing_systemv1connect.TicketingServiceClient) {
	// Call the UpdateTicketStatus method
	response, err := client.UpdateTicketStatus(context.Background(), &connect.Request[v1.UpdateTicketStatusRequest]{
		Msg: &v1.UpdateTicketStatusRequest{
			TicketId:     "1", // Assuming ticket with ID 1 exists
			NewStatus:     "IN_PROGRESS",
		},
	})
	if err != nil {
		t.Fatalf("UpdateTicketStatus failed: %v", err)
	}

	// Check if the response contains the ticket with the updated status
	if response == nil || response.Msg.Ticket == nil || response.Msg.Ticket.Status != "IN_PROGRESS" {
		t.Fatalf("UpdateTicketStatus response is nil or status not updated")
	}
}

func testListTickets(t *testing.T, client ticketing_systemv1connect.TicketingServiceClient) {
	// Call the ListTickets method
	response, err := client.ListTickets(context.Background(), &connect.Request[v1.ListTicketsRequest]{
		Msg: &v1.ListTicketsRequest{},
	})
	if err != nil {
		t.Fatalf("ListTickets failed: %v", err)
	}

	// Check if the response contains a list of tickets
	if response == nil || response.Msg.Tickets == nil || len(response.Msg.Tickets) == 0 {
		t.Fatalf("ListTickets response is nil or empty")
	}
}
