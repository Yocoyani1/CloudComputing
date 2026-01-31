# Compiler
CXX = g++

# Detect if we're using clang (macOS default)
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS: Use clang-compatible OpenMP flags with libomp
    LIBOMP_PREFIX := $(shell brew --prefix libomp 2>/dev/null || echo "/opt/homebrew/opt/libomp")
    CXXFLAGS = -Wall -Wextra -std=c++11 -Xpreprocessor -fopenmp -I$(LIBOMP_PREFIX)/include
    LDFLAGS = -L$(LIBOMP_PREFIX)/lib -lomp
else
    # Linux: Use standard g++ OpenMP flags
    CXXFLAGS = -Wall -Wextra -std=c++11 -fopenmp
    LDFLAGS =
endif

# Target executable name
TARGET = array_sum

# Source files
SRC = main.cpp

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
