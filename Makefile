CC = gcc

CFLAGS = -g -O0 -std=gnu17 -Wall -Wextra -Werror -Wshadow

LDFLAGS = -lm

SOURCES = main.c

OBJECTS = $(SOURCES:.c=.o)

TARGET = main

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf *.o

run:
	./main