module github.com/parandor/samples

go 1.21.6

replace github.com/parandor/samples/tests/go/types => ./tests/go/types

require github.com/parandor/samples/tests/go/types v0.0.0-00010101000000-000000000000

require google.golang.org/protobuf v1.32.0

require (
	connectrpc.com/connect v1.14.0
	github.com/google/go-cmp v0.6.0
	golang.org/x/net v0.20.0
)

require golang.org/x/text v0.14.0 // indirect
