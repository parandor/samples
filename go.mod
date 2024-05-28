module github.com/parandor/samples

go 1.21.6

replace github.com/parandor/samples/tests/go/types => ./tests/go/types

require github.com/parandor/samples/tests/go/types v0.0.0-00010101000000-000000000000

require google.golang.org/protobuf v1.34.1

require (
	connectrpc.com/connect v1.16.2
	github.com/google/go-cmp v0.6.0
	github.com/stretchr/testify v1.9.0
	golang.org/x/net v0.25.0
)

require (
	github.com/davecgh/go-spew v1.1.1 // indirect
	github.com/pmezard/go-difflib v1.0.0 // indirect
	golang.org/x/text v0.15.0 // indirect
	gopkg.in/yaml.v3 v3.0.1 // indirect
)
