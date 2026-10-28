CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude

BUILD_DIR = build
TARGET = $(BUILD_DIR)/turing_sim

SRC = src/main.cpp src/turing.cpp
# Maps src/filename.cpp to build/filename.o
OBJ = $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

all: $(BUILD_DIR) $(TARGET)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link the final executable inside the build folder
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files from src/ into object files in build/
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: all
	./$(TARGET)

.PHONY: all clean run