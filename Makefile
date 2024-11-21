# Compiler and linker settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I./include
LDFLAGS =

# Source and object files
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXEC = $(BIN_DIR)/my_program

# Targets
all: $(EXEC)

# Linking the object files to create the final executable
$(EXEC): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $(EXEC) $(LDFLAGS)

# Compile the source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets (not actual files)
.PHONY: all clean



