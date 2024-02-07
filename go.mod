module github.com/parandor/samples

go 1.21.6

replace github.com/parandor/samples/tests/go/types => ./tests/go/types

require github.com/parandor/samples/tests/go/types v0.0.0-00010101000000-000000000000

require google.golang.org/protobuf v1.32.0

require (
	connectrpc.com/connect v1.14.0
	github.com/google/go-cmp v0.6.0
	github.com/stretchr/testify v1.8.4
	golang.org/x/net v0.20.0
)

require (
	github.com/davecgh/go-spew v1.1.1 // indirect
	github.com/pmezard/go-difflib v1.0.0 // indirect
	golang.org/x/text v0.14.0 // indirect
	gopkg.in/yaml.v3 v3.0.1 // indirect
)
