# Compiler settings
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude -g
DEPFLAGS := -MMD -MP
LDFLAGS := 

# Directory structure
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
TARGET := $(BUILD_DIR)/main

# Auto-detect sources and headers
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Ensure build directory exists
ensure_dir = @if not exist "$(@D)" mkdir "$(@D)"

# Main target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(ensure_dir)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

# Compilation with automatic dependencies
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(ensure_dir)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPS)

run-no-build: $(TARGET)
	@echo "Running without build $(TARGET)..."
	@$(TARGET)

run: all
	@echo "Running $(TARGET)..."
	@$(TARGET)

# Clean
clean:
	del /q $(BUILD_DIR)

.PHONY: all clean