# Compiler
CC := gcc

# Directories
BUILD_DIR := build
SRC_DIR := src
INCLUDE_DIR := include
EXAMPLES_DIR := examples

# Files
SOURCE_FILES := $(wildcard $(SRC_DIR)/*.c)
HEADER_FILES := $(wildcard $(INCLUDE_DIR)/*.h)
EXAMPLE_FILES := $(wildcard $(EXAMPLES_DIR)/*.c)
OBJECT_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCE_FILES))
EXAMPLE_BINARIES := $(patsubst $(EXAMPLES_DIR)/%.c, $(BUILD_DIR)/%, $(EXAMPLE_FILES))

# Compiler flags
CFLAGS := -Wall -Wextra -I$(INCLUDE_DIR)

# Default target
all: $(EXAMPLE_BINARIES)

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Build example binaries
$(BUILD_DIR)/%: $(EXAMPLES_DIR)/%.c $(OBJECT_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

