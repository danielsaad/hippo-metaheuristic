# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20  -Wall -Wextra -O2

# Directories
SRC_DIR := src
BENCHMARK_DIR := benchmark
TEST_DIR := test
BUILD_DIR := build
BIN_DIR := bin
INCLUDE_DIR := include

# Source files
SRC := $(wildcard $(SRC_DIR)/*.cpp) 
BENCHMARK_SRC := $(wildcard $(BENCHMARK_DIR)/src/*.cpp)

BENCHMARK_APP := $(wildcard $(BENCHMARK_DIR)/*.cpp) 
TEST_APP := $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/src/%.o,$(notdir $(wildcard $(SRC_DIR)/*.cpp))) 
BENCHMARK_OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/benchmark/%.o,$(notdir $(wildcard $(BENCHMARK_DIR)/src/*.cpp)))
TEST_OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/test/%.o,$(notdir $(wildcard $(TEST_DIR)/src/*.cpp)))


BENCHMARK_BIN:= $(patsubst %.cpp,$(BENCHMARK_DIR)/%,$(notdir $(wildcard $(BENCHMARK_DIR)/*.cpp)))
TEST_BIN:= $(patsubst %.cpp,$(TEST_DIR)/%,$(notdir $(wildcard $(TEST_DIR)/*.cpp)))
# Default target

all: $(BENCHMARK_BIN) $(TEST_BIN)

# Rule to link the executable
$(BENCHMARK_BIN): $(BENCHMARK_APP) $(BENCHMARK_OBJECTS) $(OBJECTS) 
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -I$(BENCHMARK_DIR)/include  $^ -o $@

$(TEST_BIN): $(TEST_APP)  $(OBJECTS) 
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

# Rule to link the executable
$(TEST_EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@

# Rule to compile source files into object files
$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)/src
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/benchmark/%.o: $(BENCHMARK_DIR)/src/%.cpp
	@mkdir -p $(BUILD_DIR)/benchmark
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -I$(BENCHMARK_DIR)/include -c $< -o $@

$(BUILD_DIR)/test/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
