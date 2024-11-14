CC=clang
CFLAGS=-Wall -g -O0 -lm -lncurses

#SOURCE_FILES := $(patsubst %.c,%.o,$(wildcard *.c))
#HEADER_FILES := $(wildcard *.h))

BIN = battery_analyzer

all: *.c
	$(CC) $(CFLAGS) -o $(BIN) $^

clean:
	$(RM) -r *.o $(BIN)
