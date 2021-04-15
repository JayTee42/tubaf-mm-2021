CC = gcc
CFLAGS = -c -Wextra -g -O3
LD = $(CC)
LDFLAGS = -lm

TARGET = bitmap.out
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
