CC = gcc
CFLAGS = -c -Wall -Wextra -O3
LD = $(CC)
LDFLAGS = -lm

TARGET = vec_mult.out
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
