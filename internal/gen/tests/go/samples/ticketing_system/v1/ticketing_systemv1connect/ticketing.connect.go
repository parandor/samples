// Code generated by protoc-gen-connect-go. DO NOT EDIT.
//
// Source: tests/go/samples/ticketing_system/v1/ticketing.proto

package ticketing_systemv1connect

import (
	connect "connectrpc.com/connect"
	context "context"
	errors "errors"
	v1 "github.com/parandor/samples/internal/gen/tests/go/samples/ticketing_system/v1"
	http "net/http"
	strings "strings"
)

// This is a compile-time assertion to ensure that this generated file and the connect package are
// compatible. If you get a compiler error that this constant is not defined, this code was
// generated with a version of connect newer than the one compiled into your binary. You can fix the
// problem by either regenerating this code with an older version of connect or updating the connect
// version compiled into your binary.
const _ = connect.IsAtLeastVersion1_13_0

const (
	// TicketingServiceName is the fully-qualified name of the TicketingService service.
	TicketingServiceName = "tests.go.samples.ticketing_system.v1.TicketingService"
)

// These constants are the fully-qualified names of the RPCs defined in this package. They're
// exposed at runtime as Spec.Procedure and as the final two segments of the HTTP route.
//
// Note that these are different from the fully-qualified method names used by
// google.golang.org/protobuf/reflect/protoreflect. To convert from these constants to
// reflection-formatted method names, remove the leading slash and convert the remaining slash to a
// period.
const (
	// TicketingServiceCreateTicketProcedure is the fully-qualified name of the TicketingService's
	// CreateTicket RPC.
	TicketingServiceCreateTicketProcedure = "/tests.go.samples.ticketing_system.v1.TicketingService/CreateTicket"
	// TicketingServiceGetTicketByIDProcedure is the fully-qualified name of the TicketingService's
	// GetTicketByID RPC.
	TicketingServiceGetTicketByIDProcedure = "/tests.go.samples.ticketing_system.v1.TicketingService/GetTicketByID"
	// TicketingServiceListTicketsProcedure is the fully-qualified name of the TicketingService's
	// ListTickets RPC.
	TicketingServiceListTicketsProcedure = "/tests.go.samples.ticketing_system.v1.TicketingService/ListTickets"
	// TicketingServiceAddCommentProcedure is the fully-qualified name of the TicketingService's
	// AddComment RPC.
	TicketingServiceAddCommentProcedure = "/tests.go.samples.ticketing_system.v1.TicketingService/AddComment"
	// TicketingServiceUpdateTicketStatusProcedure is the fully-qualified name of the TicketingService's
	// UpdateTicketStatus RPC.
	TicketingServiceUpdateTicketStatusProcedure = "/tests.go.samples.ticketing_system.v1.TicketingService/UpdateTicketStatus"
)

// These variables are the protoreflect.Descriptor objects for the RPCs defined in this package.
var (
	ticketingServiceServiceDescriptor                  = v1.File_tests_go_samples_ticketing_system_v1_ticketing_proto.Services().ByName("TicketingService")
	ticketingServiceCreateTicketMethodDescriptor       = ticketingServiceServiceDescriptor.Methods().ByName("CreateTicket")
	ticketingServiceGetTicketByIDMethodDescriptor      = ticketingServiceServiceDescriptor.Methods().ByName("GetTicketByID")
	ticketingServiceListTicketsMethodDescriptor        = ticketingServiceServiceDescriptor.Methods().ByName("ListTickets")
	ticketingServiceAddCommentMethodDescriptor         = ticketingServiceServiceDescriptor.Methods().ByName("AddComment")
	ticketingServiceUpdateTicketStatusMethodDescriptor = ticketingServiceServiceDescriptor.Methods().ByName("UpdateTicketStatus")
)

// TicketingServiceClient is a client for the tests.go.samples.ticketing_system.v1.TicketingService
// service.
type TicketingServiceClient interface {
	// CreateTicket creates a new support ticket
	CreateTicket(context.Context, *connect.Request[v1.CreateTicketRequest]) (*connect.Response[v1.CreateTicketResponse], error)
	// GetTicketByID retrieves a support ticket by its ID
	GetTicketByID(context.Context, *connect.Request[v1.GetTicketByIDRequest]) (*connect.Response[v1.GetTicketByIDResponse], error)
	// ListTickets lists all support tickets
	ListTickets(context.Context, *connect.Request[v1.ListTicketsRequest]) (*connect.Response[v1.ListTicketsResponse], error)
	// AddComment adds a comment to a ticket
	AddComment(context.Context, *connect.Request[v1.AddCommentRequest]) (*connect.Response[v1.AddCommentResponse], error)
	// UpdateTicketStatus updates the status of a ticket
	UpdateTicketStatus(context.Context, *connect.Request[v1.UpdateTicketStatusRequest]) (*connect.Response[v1.UpdateTicketStatusResponse], error)
}

// NewTicketingServiceClient constructs a client for the
// tests.go.samples.ticketing_system.v1.TicketingService service. By default, it uses the Connect
// protocol with the binary Protobuf Codec, asks for gzipped responses, and sends uncompressed
// requests. To use the gRPC or gRPC-Web protocols, supply the connect.WithGRPC() or
// connect.WithGRPCWeb() options.
//
// The URL supplied here should be the base URL for the Connect or gRPC server (for example,
// http://api.acme.com or https://acme.com/grpc).
func NewTicketingServiceClient(httpClient connect.HTTPClient, baseURL string, opts ...connect.ClientOption) TicketingServiceClient {
	baseURL = strings.TrimRight(baseURL, "/")
	return &ticketingServiceClient{
		createTicket: connect.NewClient[v1.CreateTicketRequest, v1.CreateTicketResponse](
			httpClient,
			baseURL+TicketingServiceCreateTicketProcedure,
			connect.WithSchema(ticketingServiceCreateTicketMethodDescriptor),
			connect.WithClientOptions(opts...),
		),
		getTicketByID: connect.NewClient[v1.GetTicketByIDRequest, v1.GetTicketByIDResponse](
			httpClient,
			baseURL+TicketingServiceGetTicketByIDProcedure,
			connect.WithSchema(ticketingServiceGetTicketByIDMethodDescriptor),
			connect.WithClientOptions(opts...),
		),
		listTickets: connect.NewClient[v1.ListTicketsRequest, v1.ListTicketsResponse](
			httpClient,
			baseURL+TicketingServiceListTicketsProcedure,
			connect.WithSchema(ticketingServiceListTicketsMethodDescriptor),
			connect.WithClientOptions(opts...),
		),
		addComment: connect.NewClient[v1.AddCommentRequest, v1.AddCommentResponse](
			httpClient,
			baseURL+TicketingServiceAddCommentProcedure,
			connect.WithSchema(ticketingServiceAddCommentMethodDescriptor),
			connect.WithClientOptions(opts...),
		),
		updateTicketStatus: connect.NewClient[v1.UpdateTicketStatusRequest, v1.UpdateTicketStatusResponse](
			httpClient,
			baseURL+TicketingServiceUpdateTicketStatusProcedure,
			connect.WithSchema(ticketingServiceUpdateTicketStatusMethodDescriptor),
			connect.WithClientOptions(opts...),
		),
	}
}

// ticketingServiceClient implements TicketingServiceClient.
type ticketingServiceClient struct {
	createTicket       *connect.Client[v1.CreateTicketRequest, v1.CreateTicketResponse]
	getTicketByID      *connect.Client[v1.GetTicketByIDRequest, v1.GetTicketByIDResponse]
	listTickets        *connect.Client[v1.ListTicketsRequest, v1.ListTicketsResponse]
	addComment         *connect.Client[v1.AddCommentRequest, v1.AddCommentResponse]
	updateTicketStatus *connect.Client[v1.UpdateTicketStatusRequest, v1.UpdateTicketStatusResponse]
}

// CreateTicket calls tests.go.samples.ticketing_system.v1.TicketingService.CreateTicket.
func (c *ticketingServiceClient) CreateTicket(ctx context.Context, req *connect.Request[v1.CreateTicketRequest]) (*connect.Response[v1.CreateTicketResponse], error) {
	return c.createTicket.CallUnary(ctx, req)
}

// GetTicketByID calls tests.go.samples.ticketing_system.v1.TicketingService.GetTicketByID.
func (c *ticketingServiceClient) GetTicketByID(ctx context.Context, req *connect.Request[v1.GetTicketByIDRequest]) (*connect.Response[v1.GetTicketByIDResponse], error) {
	return c.getTicketByID.CallUnary(ctx, req)
}

// ListTickets calls tests.go.samples.ticketing_system.v1.TicketingService.ListTickets.
func (c *ticketingServiceClient) ListTickets(ctx context.Context, req *connect.Request[v1.ListTicketsRequest]) (*connect.Response[v1.ListTicketsResponse], error) {
	return c.listTickets.CallUnary(ctx, req)
}

// AddComment calls tests.go.samples.ticketing_system.v1.TicketingService.AddComment.
func (c *ticketingServiceClient) AddComment(ctx context.Context, req *connect.Request[v1.AddCommentRequest]) (*connect.Response[v1.AddCommentResponse], error) {
	return c.addComment.CallUnary(ctx, req)
}

// UpdateTicketStatus calls
// tests.go.samples.ticketing_system.v1.TicketingService.UpdateTicketStatus.
func (c *ticketingServiceClient) UpdateTicketStatus(ctx context.Context, req *connect.Request[v1.UpdateTicketStatusRequest]) (*connect.Response[v1.UpdateTicketStatusResponse], error) {
	return c.updateTicketStatus.CallUnary(ctx, req)
}

// TicketingServiceHandler is an implementation of the
// tests.go.samples.ticketing_system.v1.TicketingService service.
type TicketingServiceHandler interface {
	// CreateTicket creates a new support ticket
	CreateTicket(context.Context, *connect.Request[v1.CreateTicketRequest]) (*connect.Response[v1.CreateTicketResponse], error)
	// GetTicketByID retrieves a support ticket by its ID
	GetTicketByID(context.Context, *connect.Request[v1.GetTicketByIDRequest]) (*connect.Response[v1.GetTicketByIDResponse], error)
	// ListTickets lists all support tickets
	ListTickets(context.Context, *connect.Request[v1.ListTicketsRequest]) (*connect.Response[v1.ListTicketsResponse], error)
	// AddComment adds a comment to a ticket
	AddComment(context.Context, *connect.Request[v1.AddCommentRequest]) (*connect.Response[v1.AddCommentResponse], error)
	// UpdateTicketStatus updates the status of a ticket
	UpdateTicketStatus(context.Context, *connect.Request[v1.UpdateTicketStatusRequest]) (*connect.Response[v1.UpdateTicketStatusResponse], error)
}

// NewTicketingServiceHandler builds an HTTP handler from the service implementation. It returns the
// path on which to mount the handler and the handler itself.
//
// By default, handlers support the Connect, gRPC, and gRPC-Web protocols with the binary Protobuf
// and JSON codecs. They also support gzip compression.
func NewTicketingServiceHandler(svc TicketingServiceHandler, opts ...connect.HandlerOption) (string, http.Handler) {
	ticketingServiceCreateTicketHandler := connect.NewUnaryHandler(
		TicketingServiceCreateTicketProcedure,
		svc.CreateTicket,
		connect.WithSchema(ticketingServiceCreateTicketMethodDescriptor),
		connect.WithHandlerOptions(opts...),
	)
	ticketingServiceGetTicketByIDHandler := connect.NewUnaryHandler(
		TicketingServiceGetTicketByIDProcedure,
		svc.GetTicketByID,
		connect.WithSchema(ticketingServiceGetTicketByIDMethodDescriptor),
		connect.WithHandlerOptions(opts...),
	)
	ticketingServiceListTicketsHandler := connect.NewUnaryHandler(
		TicketingServiceListTicketsProcedure,
		svc.ListTickets,
		connect.WithSchema(ticketingServiceListTicketsMethodDescriptor),
		connect.WithHandlerOptions(opts...),
	)
	ticketingServiceAddCommentHandler := connect.NewUnaryHandler(
		TicketingServiceAddCommentProcedure,
		svc.AddComment,
		connect.WithSchema(ticketingServiceAddCommentMethodDescriptor),
		connect.WithHandlerOptions(opts...),
	)
	ticketingServiceUpdateTicketStatusHandler := connect.NewUnaryHandler(
		TicketingServiceUpdateTicketStatusProcedure,
		svc.UpdateTicketStatus,
		connect.WithSchema(ticketingServiceUpdateTicketStatusMethodDescriptor),
		connect.WithHandlerOptions(opts...),
	)
	return "/tests.go.samples.ticketing_system.v1.TicketingService/", http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		switch r.URL.Path {
		case TicketingServiceCreateTicketProcedure:
			ticketingServiceCreateTicketHandler.ServeHTTP(w, r)
		case TicketingServiceGetTicketByIDProcedure:
			ticketingServiceGetTicketByIDHandler.ServeHTTP(w, r)
		case TicketingServiceListTicketsProcedure:
			ticketingServiceListTicketsHandler.ServeHTTP(w, r)
		case TicketingServiceAddCommentProcedure:
			ticketingServiceAddCommentHandler.ServeHTTP(w, r)
		case TicketingServiceUpdateTicketStatusProcedure:
			ticketingServiceUpdateTicketStatusHandler.ServeHTTP(w, r)
		default:
			http.NotFound(w, r)
		}
	})
}

// UnimplementedTicketingServiceHandler returns CodeUnimplemented from all methods.
type UnimplementedTicketingServiceHandler struct{}

func (UnimplementedTicketingServiceHandler) CreateTicket(context.Context, *connect.Request[v1.CreateTicketRequest]) (*connect.Response[v1.CreateTicketResponse], error) {
	return nil, connect.NewError(connect.CodeUnimplemented, errors.New("tests.go.samples.ticketing_system.v1.TicketingService.CreateTicket is not implemented"))
}

func (UnimplementedTicketingServiceHandler) GetTicketByID(context.Context, *connect.Request[v1.GetTicketByIDRequest]) (*connect.Response[v1.GetTicketByIDResponse], error) {
	return nil, connect.NewError(connect.CodeUnimplemented, errors.New("tests.go.samples.ticketing_system.v1.TicketingService.GetTicketByID is not implemented"))
}

func (UnimplementedTicketingServiceHandler) ListTickets(context.Context, *connect.Request[v1.ListTicketsRequest]) (*connect.Response[v1.ListTicketsResponse], error) {
	return nil, connect.NewError(connect.CodeUnimplemented, errors.New("tests.go.samples.ticketing_system.v1.TicketingService.ListTickets is not implemented"))
}

func (UnimplementedTicketingServiceHandler) AddComment(context.Context, *connect.Request[v1.AddCommentRequest]) (*connect.Response[v1.AddCommentResponse], error) {
	return nil, connect.NewError(connect.CodeUnimplemented, errors.New("tests.go.samples.ticketing_system.v1.TicketingService.AddComment is not implemented"))
}

func (UnimplementedTicketingServiceHandler) UpdateTicketStatus(context.Context, *connect.Request[v1.UpdateTicketStatusRequest]) (*connect.Response[v1.UpdateTicketStatusResponse], error) {
	return nil, connect.NewError(connect.CodeUnimplemented, errors.New("tests.go.samples.ticketing_system.v1.TicketingService.UpdateTicketStatus is not implemented"))
}
