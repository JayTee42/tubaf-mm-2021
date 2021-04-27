CC = gcc
CFLAGS = -c -Wall -Os
LD = $(CC)
LDFLAGS = -lm

TARGET = inline_asm.out
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -fomit-frame-pointer -S $^ -o $@.asm -masm=intel
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) *.asm
