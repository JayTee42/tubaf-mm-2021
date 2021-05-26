CC=gcc
CFLAGS =-c -Wextra -O3
LD=$(CC)
LDFLAGS=-lm

TARGET=dctquant.out
OBJECTS=$(patsubst %.c, %.o, $(wildcard *.c))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
