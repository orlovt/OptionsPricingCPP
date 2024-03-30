# Compiler and linker configuration
# CXX = g++
# # CXXFLAGS = -Wall -Wextra -std=c++17 -I/opt/homebrew/opt/eigen/include/eigen3 -Iinclude
# # LDFLAGS =
# CXXFLAGS = -Wall -Wextra -std=c++17 -fopenmp -I/opt/homebrew/opt/eigen/include/eigen3 -Iinclude -I/opt/homebrew/opt/libomp/include
# LDFLAGS = -L/opt/homebrew/opt/libomp/lib -fopenmp
CXX = g++-13
CXXFLAGS = -Wall -Wextra -std=c++17 -fopenmp -I/opt/homebrew/opt/eigen/include/eigen3 -Iinclude -I/opt/homebrew/opt/libomp/include
LDFLAGS = -L/opt/homebrew/opt/libomp/lib -fopenmp

# Directory configuration
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj
INCLUDE_DIR = include

# Find all .cpp files in the SRC_DIR and its subdirectories
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
# Replace the directory and extension of source files to obtain object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Target executable name
# TARGET = $(BIN_DIR)/price
TARGET = price_opt

# Phony targets for build and clean
.PHONY: all clean directories

all: directories $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/Factory
	@mkdir -p $(OBJ_DIR)/domain
	@mkdir -p $(OBJ_DIR)/models
	@mkdir -p $(OBJ_DIR)/util

clean:
	@rm -rf $(BIN_DIR)
