# Makefile for the Banking Management System

CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/account.c $(SRC_DIR)/fileManagement.c
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/account.o $(OBJ_DIR)/fileManagement.o
TARGET = $(BIN_DIR)/banking_management

# Default target
all: $(TARGET)

# Compile and link the target
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create the binary directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the application
run: $(TARGET)
	./$(TARGET)

# Create the data directory if not exists
$(DATA_DIR):
	mkdir -p $(DATA_DIR)

.PHONY: all clean run
