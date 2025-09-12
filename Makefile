# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -I./include -I./benchmark -Wall -Wextra -O2

# Directories
SRCDIR := src
BENCHMARKDIR := benchmark
BUILDDIR := build
BINDIR := bin

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(BENCHMARKDIR)/*.cpp)

# Object files (preserve directory structure)
OBJECTS := $(patsubst %.cpp,$(BUILDDIR)/src/%.o,$(notdir $(wildcard $(SRCDIR)/*.cpp))) \
		   $(patsubst %.cpp,$(BUILDDIR)/benchmark/%.o,$(notdir $(wildcard $(BENCHMARKDIR)/*.cpp)))

# Executable name
EXECUTABLE := $(BINDIR)/benchmark

# Default target
all: $(EXECUTABLE)

# Rule to link the executable
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $@

# Rule to compile source files into object files
$(BUILDDIR)/src/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)/src
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/benchmark/%.o: $(BENCHMARKDIR)/%.cpp
	@mkdir -p $(BUILDDIR)/benchmark
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

.PHONY: all clean
