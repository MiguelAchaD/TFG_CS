CXX = g++
LIBS = -lcurl
CXXFLAGS = -Wall -Wextra -Iinclude -Iinclude/Sockets -std=c++17
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin
PROGRAM_LOG_DIR = $(BIN_DIR)/logs
TARGET = $(BIN_DIR)/main

SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)
	@echo "Compiled $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET) $(PROGRAM_LOG_DIR)/*
	@echo "Compiled files deleted."

run: all
	./$(TARGET)

.PHONY: clean all run
