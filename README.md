# Enhanced Student Registry System

An interactive, command-line Student Registry application written in C. This program utilizes functional abstraction principles and handles dynamic data management with persistence between executions.

## Compilation and Execution Instructions

### Using Makefile
* **Compile:** Run `make` in your terminal to build the application.
* **Compile and Run:** Run `make run` to build and immediately start the program.
* **Clean:** Run `make clean` to drop generated object files and binaries.

### Manual Compilation
If `make` is unavailable on your system, execute the following instructions explicitly:
```bash
gcc -c student_registry.c -o student_registry.o
gcc -c main.c -o main.o
gcc student_registry.o main.o -o student_registry
./student_registry
