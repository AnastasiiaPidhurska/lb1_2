CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = 

SRC = src/main.c src/stats.c src/arraylist.c
OBJ = $(SRC:.c=.o)
TARGET = monitor

all: build $(TARGET)

build:
	mkdir -p bin obj

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o bin/$@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./bin/$(TARGET) -p -v -t 2 -n 3

clean:
	rm -rf bin obj src/*.o

.PHONY: all build run clean
