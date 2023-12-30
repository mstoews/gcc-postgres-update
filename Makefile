DB_URL=postgresql://root:secret@localhost:5432/simple_bank?sslmode=disable

build:
	g++ main.cpp ./tables/glaccounts.cpp ./tables/gltypes.cpp ./tables/gltransactions.cpp  -lpqxx -lpq -lpthread -o webserver

run:
	./webserver 

.PHONY: build run
