CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = student_registry
OBJ = student_registry.o main.o

# Default rule to compile everything
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile individual source files into object files
%.o: %.c student_registry.h
	$(CC) $(CFLAGS) -c $< -o $@

# Shortcut rule to compile and run instantly
run: all
	./$(TARGET)

# Clean up build outputs
clean:
	rm -f *.o $(TARGET)

.PHONY: all run clean