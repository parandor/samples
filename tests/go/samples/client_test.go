package samples

import (
	"context"
	"fmt"
	"net/http"
	"testing"

	connect "connectrpc.com/connect"
	v1 "github.com/parandor/samples/internal/gen/tests/go/samples/ping/v1"
	pingv1connect "github.com/parandor/samples/internal/gen/tests/go/samples/ping/v1/pingv1connect"
)

func TestExampleClient(t *testing.T) {
	// Create a new PingServiceClient
	client := pingv1connect.NewPingServiceClient(http.DefaultClient, "http://localhost:8080")

	// Example: Call Ping
	//pingReq := &v1.PingRequest{Message: "Hello", Counter: 42}
	pingResp, err := client.Ping(context.Background(),
		connect.NewRequest(&v1.PingRequest{
			Message: "Hello world",
			Counter: 0,
		}),
	)
	if err != nil {
		t.Fatalf("Ping failed: %s", pingResp)
	}
	fmt.Println("Ping Response:", pingResp)

	// Example: Call GetServerInfo
	serverInfoResp, err := client.GetServerInfo(context.Background(), &connect.Request[v1.GetServerInfoRequest]{
		Msg: &v1.GetServerInfoRequest{},
	})
	if err != nil {
		t.Fatalf("GetServerInfo failed: %s", serverInfoResp)
	}
	fmt.Println("Server Info Response:", serverInfoResp)
}
