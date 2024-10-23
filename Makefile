# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
TEST_DIR = ./Tests

# Source files
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/Gates.cpp \
       $(SRC_DIR)/ParseVerilog.cpp \
       $(SRC_DIR)/ParseStim.cpp

# Object files
OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/Gates.o \
       $(OBJ_DIR)/ParseVerilog.o \
       $(OBJ_DIR)/ParseStim.o

# Output executable
EXEC = circuit_simulator

# Default target
all: $(EXEC)

# Link object files to create the final executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)

# Run the executable with tests
run: $(EXEC)
	./$(EXEC) $(TEST_DIR)/parity_checker.v $(TEST_DIR)/stimulus.txt

.PHONY: all clean run
