CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c99

SOURCE = $(wildcard Source/*/*.c)
SOURCE := $(filter-out Source/main.c)
SOURCE_O = (SOURCE:c=o)


all: %.o
	$(CC) $(CFLAGS) 

.PHONY: clean
clean:
	rm *.o main
