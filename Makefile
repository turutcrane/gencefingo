#

template.qtpl.go: template.qtpl
	go generate *.go

parser/parse_string.go: parser/parse.go
	go generate ./parser/parse.go

.PHONY: vet
vet: template.qtpl.go *.go parser/parse_string.go
	@# adjust path produced in error meesage
	go vet .

capi:
	go run . -pkgdir ../cefingo

.PHONY: fmt
fmt:
	go fmt *.go
	go fmt parser/*.go
