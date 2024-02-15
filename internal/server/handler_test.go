package server_test

import (
	"context"
	"fmt"
	"net/http"
	"testing"
	"time"

	"github.com/parandor/samples/internal/memhttp"
	"github.com/parandor/samples/internal/server"
	"google.golang.org/protobuf/types/known/timestamppb"

	connect "connectrpc.com/connect"
	pingv1 "github.com/parandor/samples/internal/gen/tests/go/samples/ping/v1"
	pingv1connect "github.com/parandor/samples/internal/gen/tests/go/samples/ping/v1/pingv1connect"
)

func TestPingHandlerAndClient(t *testing.T) {

	mux := http.NewServeMux()
	mux.Handle(server.NewMyPingServiceHandler())
	listener := memhttp.NewServer(mux)

	c := pingv1connect.NewPingServiceClient(
		listener.Client(),
		listener.URL(),
		connect.WithInterceptors(server.NewAuthInterceptor("super-secret")))

	t_start := timestamppb.New(time.Now())
	number := int32(123)
	pingResp, err := c.Ping(context.Background(),
		connect.NewRequest(&pingv1.PingRequest{
			Message: "Hello ",
			Number:  number,
		}),
	)
	_, err = server.HandleResponse(pingResp, err)
	if err != nil {
		t.Fatalf("Ping failed: %s", err)
	}

	timeDifference := pingResp.Msg.ProcessedAt.AsTime().Sub(t_start.AsTime())
	if timeDifference > 10*time.Millisecond {
		t.Fatalf("Ping failed: expected msg ping duration of %d ms but got %d ms", 10, timeDifference)
	} else {
		fmt.Println("Msg took", timeDifference.Microseconds(), "us")
	}

	if pingResp.Msg.Number != number {
		t.Fatalf("Ping failed: expected %d but got %d", number, pingResp.Msg.Number)
	}

	if pingResp.Msg.Reply != "Hello World" {
		t.Fatalf("Ping failed: expected %s but got %s", "Hello World", pingResp.Msg.Reply)
	}

	// Example: Call GetServerInfo
	serverInfoResp, err := c.GetServerInfo(context.Background(), connect.NewRequest(&pingv1.GetServerInfoRequest{}))
	if err != nil {
		t.Fatalf("GetServerInfo failed: %s", serverInfoResp)
	}

	if serverInfoResp.Msg.ServerName != "MyServer" {
		t.Fatalf("GetServerInfo failed: expected %s but got %s", "MyServer", serverInfoResp.Msg.ServerName)
	}
}

func TestClientAuthFailure(t *testing.T) {
	mux := http.NewServeMux()
	mux.Handle(server.NewMyPingServiceHandler())
	listener := memhttp.NewServer(mux)

	c := pingv1connect.NewPingServiceClient(
		listener.Client(),
		listener.URL(),
		connect.WithInterceptors(server.NewAuthInterceptor("wrong-secret")))

	number := int32(123)
	pingResp, err := c.Ping(context.Background(),
		connect.NewRequest(&pingv1.PingRequest{
			Message: "Hello ",
			Number:  number,
		}),
	)
	_, err = server.HandleResponse(pingResp, err)
	if err == nil {
		t.Fatalf("Ping failed: %s", err)
	}
	fmt.Println(err.Error())
}
