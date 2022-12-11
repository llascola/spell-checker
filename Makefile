CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c99

BIN = main

SOURCE = $(wildcard Source/*.c)
SOURCE := $(filter-out Source/main.c, $(SOURCE))
SOURCE_O = $(SOURCE:c=o)

STRUCTURES = $(wildcard Structures/*.c)
STRUCTURES_O = $(STRUCTURES:c=o)

all: Source/main.o $(SOURCE_O) $(STRUCTURES_O)
	$(CC) $(CFLAGS) $^ -o $(BIN)
	
%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

.PHONY: debug
debug: Source/main.c
	$(CC) -g $(CFLAGS) Source/main.c $(SOURCE) $(STRUCTURES)  -o $(BIN)

.PHONY: clean
clean:
	@rm -r *.dSYM 2>/dev/null || true
	@rm Source/*.o Structures/*.o 2>/dev/null || true
	@rm $(BIN) 2>/dev/null || true
