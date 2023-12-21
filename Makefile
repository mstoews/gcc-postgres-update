DB_URL=postgresql://root:secret@localhost:5432/simple_bank?sslmode=disable

build:
	g++ main.cpp ./tables/glaccounts.cpp ./tables/gltypes.cpp  -lpqxx -lpq -o gl

run:
	./glaccounts -t

.PHONY: build
