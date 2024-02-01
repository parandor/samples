module github.com/parandor/samples

go 1.21.6

replace github.com/parandor/samples/tests/go/types => ./tests/go/types

require github.com/parandor/samples/tests/go/types v0.0.0-00010101000000-000000000000

require google.golang.org/protobuf v1.32.0

require (
	connectrpc.com/connect v1.14.0
	github.com/google/go-cmp v0.5.9
	golang.org/x/net v0.17.0
)

require golang.org/x/text v0.13.0 // indirect
