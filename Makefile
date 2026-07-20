CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = student_registry
OBJ = student_registry.o main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c student_registry.h
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)

.PHONY: all run clean
