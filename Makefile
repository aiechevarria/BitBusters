# Compiler and flags
CC = gcc
#CFLAGS = -Wall -Wextra -O0 -g
CFLAGS = -O0 -g

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Executable name
EXEC = $(BUILD_DIR)/my_program

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile all .c files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean build files
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Default target
all: $(EXEC)
