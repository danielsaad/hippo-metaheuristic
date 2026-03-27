CXX = g++
# CXXFLAGS = -std=c++23 -Wall -Wextra -O2 -MMD -MP
CXXFLAGS = -std=c++23 -Wall -Wextra -g -MMD -MP
INCLUDES = -Iinclude

SRC_DIR = src
APP_DIR = apps
OBJ_DIR = build/obj
BIN_DIR = bin

# Recursive source discovery
SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

APP_SRC = $(shell find $(APP_DIR) -name '*.cpp')
APPS = $(patsubst $(APP_DIR)/%.cpp,$(BIN_DIR)/%,$(APP_SRC))

all: $(APPS)

# Build executables
$(BIN_DIR)/%: $(APP_DIR)/%.cpp $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Compile source files (preserve subdirectories)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf build

-include $(OBJ:.o=.d)
