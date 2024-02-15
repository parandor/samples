package server

import (
	"context"
	"errors"
	"fmt"

	"connectrpc.com/connect"
)

const tokenHeader = "TokenHeader"

var validTokens = map[string]bool{
	"super-secret":     true,
	"even-more-secret": true,
	// Add more valid tokens here if needed
}

func NewAuthInterceptor(token string) connect.UnaryInterceptorFunc {
	interceptor := func(next connect.UnaryFunc) connect.UnaryFunc {
		return connect.UnaryFunc(func(
			ctx context.Context,
			req connect.AnyRequest,
		) (connect.AnyResponse, error) {
			if req.Spec().IsClient {
				// Send a token with client requests if provided.
				if token != "" {
					req.Header().Set(tokenHeader, token)
				}
			} else {
				reqToken := req.Header().Get(tokenHeader)
				if reqToken == "" {
					// Check token in handlers.
					return nil, connect.NewError(
						connect.CodeUnauthenticated,
						errors.New("no token provided"),
					)
				} else if !validTokens[reqToken] {
					// Invalid token provided.
					return nil, connect.NewError(
						connect.CodePermissionDenied,
						errors.New("invalid token"),
					)
				}
			}
			return next(ctx, req)
		})
	}
	return connect.UnaryInterceptorFunc(interceptor)
}

func HandleResponse(response connect.AnyResponse, err error) (connect.AnyResponse, error) {
	// Check for authentication errors
	if err != nil {
		// Check if the error is a connect.Error
		if connectErr, ok := err.(*connect.Error); ok {
			// Check the error code
			switch connectErr.Code() {
			case connect.CodeUnauthenticated:
				return nil, errors.New("authentication failed: no token provided")
			case connect.CodePermissionDenied:
				return nil, errors.New("authentication failed: invalid token")
			default:
				return nil, fmt.Errorf("RPC error: %v", err)
			}
		}
		return nil, fmt.Errorf("RPC error: %v", err)
	}

	// No error, return response
	return response, nil
}
