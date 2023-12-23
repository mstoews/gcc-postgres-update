DB_URL=postgresql://root:secret@localhost:5432/simple_bank?sslmode=disable

build:
	g++ main.cpp ./tables/glaccounts.cpp ./tables/gltypes.cpp ./tables/gltransactions.cpp  -lpqxx -lpq -o gl

run:
	./gl 

.PHONY: build
