DB_URL=postgresql://root:secret@localhost:5432/simple_bank?sslmode=disable

build:
	g++ main.cpp glaccounts.cpp -lpqxx -lpq -o glaccounts

run:
	./glaccounts -t

.PHONY: build
