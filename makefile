
CC = g++
CFLAGS = -g -Wall -fopenmp

A_PATH = data/example/example_A.mtx
B_PATH = data/example/example_b.mtx

MODE = naive

.PHONY: example test build clean
test:
	./build/test $(A_PATH) $(B_PATH) $(MODE)

build:
	$(CC) $(CFLAGS) src/main.cpp -o build/test

clean:
	rm -rf build/*
