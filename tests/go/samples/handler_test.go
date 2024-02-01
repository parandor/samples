// handler.go

package samples

import (
	"context"
	"net/http"
	"time"
	"testing"

	connect "connectrpc.com/connect"
	v1 "github.com/parandor/samples/internal/gen/tests/go/samples/ping/v1"
	pingv1connect "github.com/parandor/samples/internal/gen/tests/go/samples/ping/v1/pingv1connect"
	"google.golang.org/protobuf/types/known/timestamppb"
)

// MyPingServiceHandler is your implementation of the PingServiceHandler interface
type MyPingServiceHandler struct {
	// Add any necessary fields for your implementation
}

// Implement the Ping method
func (h *MyPingServiceHandler) Ping(ctx context.Context, req *connect.Request[v1.PingRequest]) (*connect.Response[v1.PingResponse], error) {

	// Your implementation logic for Ping method
	response := &connect.Response[v1.PingResponse]{
		Msg: &v1.PingResponse{
			Reply: "Pong",
			ProcessedAt: timestamppb.New(time.Now()),
		},
	}
	return response, nil
}

// Implement the GetServerInfo method
func (h *MyPingServiceHandler) GetServerInfo(ctx context.Context, req *connect.Request[v1.GetServerInfoRequest]) (*connect.Response[v1.GetServerInfoResponse], error) {
	// Your implementation logic for GetServerInfo method
    response := &connect.Response[v1.GetServerInfoResponse]{
    	Msg: &v1.GetServerInfoResponse{
			ServerName:    "MyServer",
			ServerVersion: "1.0",
			CurrentTime:   timestamppb.New(time.Now()),
    	},
    }
	return response, nil
}

// Create an HTTP server handler using NewPingServiceHandler function
func NewMyPingServiceHandler() (string, http.Handler) {
	handler := &MyPingServiceHandler{}
	
	// Use NewPingServiceHandler to create the HTTP handler
	path, httpHandler := pingv1connect.NewPingServiceHandler(handler)

	// Optionally, you can add middleware or modify the http.Handler here

	return path, httpHandler
}

// Example main function to start the HTTP server
func TestExampleHandler(t *testing.T) {
	path, httpHandler := NewMyPingServiceHandler()

	// Mount the HTTP handler at the specified path
	http.Handle(path, httpHandler)

	// Start the HTTP server
	if err := http.ListenAndServe("localhost:8080", nil); err != nil {
		panic(err)
	}
}
