package server

import (
	"context"
	"errors"
	"net/http"
	"sync"

	connect "connectrpc.com/connect"
	v1 "github.com/parandor/samples/internal/gen/tests/go/samples/ticketing_system/v1"
	ticketing_systemv1connect "github.com/parandor/samples/internal/gen/tests/go/samples/ticketing_system/v1/ticketing_systemv1connect"
)

// MyTicketingServiceHandler is an implementation of the TicketingServiceHandler interface.
type MyTicketingServiceHandler struct {
	tickets map[string]*v1.Ticket // Map to store tickets by ID
	mu      sync.Mutex            // Mutex to ensure safe access to the map
}

// NewMyTicketingServiceHandler creates a new instance of MyTicketingServiceHandler.
func NewMyTicketingServiceHandler() (string, http.Handler) {
	handler := &MyTicketingServiceHandler{
		tickets: make(map[string]*v1.Ticket),
	}

	// Use NewTicketingServiceHandler to create the HTTP handler
	path, httpHandler := ticketing_systemv1connect.NewTicketingServiceHandler(handler)

	// Optionally, you can add middleware or modify the http.Handler here

	return path, httpHandler
}

// CreateTicket implements the CreateTicket method of TicketingServiceHandler.
func (h *MyTicketingServiceHandler) CreateTicket(ctx context.Context, req *connect.Request[v1.CreateTicketRequest]) (*connect.Response[v1.CreateTicketResponse], error) {
	// Extract the ticket from the request
	newTicket := req.Msg.Ticket

	// Generate a unique ID for the ticket (you may use a UUID library for this purpose)
	// For demonstration, let's assume the ID is provided by the client
	ticketID := newTicket.GetId()

	// Lock the map to ensure safe access
	h.mu.Lock()
	defer h.mu.Unlock()

	// Check if the ticket already exists
	if _, ok := h.tickets[ticketID]; ok {
		return nil, connect.NewError(connect.CodeAlreadyExists, errors.New("ticket already exists"))
	}

	// Store the new ticket in the map
	h.tickets[ticketID] = newTicket

	// Return the response indicating success
	response := &v1.CreateTicketResponse{Ticket: newTicket}
	return connect.NewResponse(response), nil
}

// GetTicketByID implements the GetTicketByID method of TicketingServiceHandler.
func (h *MyTicketingServiceHandler) GetTicketByID(ctx context.Context, req *connect.Request[v1.GetTicketByIDRequest]) (*connect.Response[v1.GetTicketByIDResponse], error) {
	// Extract the ticket ID from the request
	ticketID := req.Msg.Id

	// Lock the map to ensure safe access
	h.mu.Lock()
	defer h.mu.Unlock()

	// Check if the ticket exists in the map
	ticket, ok := h.tickets[ticketID]
	if !ok {
		return nil, connect.NewError(connect.CodeNotFound, errors.New("ticket not found"))
	}

	// Return the response containing the ticket
	response := &v1.GetTicketByIDResponse{Ticket: ticket}
	return connect.NewResponse(response), nil
}

// ListTickets implements the ListTickets method of TicketingServiceHandler.
func (h *MyTicketingServiceHandler) ListTickets(ctx context.Context, req *connect.Request[v1.ListTicketsRequest]) (*connect.Response[v1.ListTicketsResponse], error) {
	// Lock the map to ensure safe access
	h.mu.Lock()
	defer h.mu.Unlock()

	// Initialize a slice to store the tickets
	var ticketList []*v1.Ticket

	// Iterate over the tickets map and append each ticket to the slice
	for _, ticket := range h.tickets {
		ticketList = append(ticketList, ticket)
	}

	// Create a response containing the list of tickets
	response := &v1.ListTicketsResponse{Tickets: ticketList}
	return connect.NewResponse(response), nil
}

// AddComment implements the AddComment method of TicketingServiceHandler.
func (h *MyTicketingServiceHandler) AddComment(ctx context.Context, req *connect.Request[v1.AddCommentRequest]) (*connect.Response[v1.AddCommentResponse], error) {
	// Extract the ticket ID and comment from the request
	ticketID := req.Msg.TicketId
	comment := req.Msg.Comment

	// Lock the map to ensure safe access
	h.mu.Lock()
	defer h.mu.Unlock()

	// Check if the ticket exists in the map
	ticket, ok := h.tickets[ticketID]
	if !ok {
		return nil, connect.NewError(connect.CodeNotFound, errors.New("ticket not found"))
	}

	// Add the comment to the ticket
	ticket.Comments = append(ticket.Comments, comment)

	// Return the response indicating success
	response := &v1.AddCommentResponse{Ticket: ticket}
	return connect.NewResponse(response), nil
}

// UpdateTicketStatus implements the UpdateTicketStatus method of TicketingServiceHandler.
func (h *MyTicketingServiceHandler) UpdateTicketStatus(ctx context.Context, req *connect.Request[v1.UpdateTicketStatusRequest]) (*connect.Response[v1.UpdateTicketStatusResponse], error) {
	// Extract the ticket ID and status from the request
	ticketID := req.Msg.TicketId
	status := req.Msg.NewStatus

	// Lock the map to ensure safe access
	h.mu.Lock()
	defer h.mu.Unlock()

	// Check if the ticket exists in the map
	ticket, ok := h.tickets[ticketID]
	if !ok {
		return nil, connect.NewError(connect.CodeNotFound, errors.New("ticket not found"))
	}

	// Update the status of the ticket
	ticket.Status = status

	// Return the response indicating success
	response := &v1.UpdateTicketStatusResponse{Ticket: ticket}
	return connect.NewResponse(response), nil
}
