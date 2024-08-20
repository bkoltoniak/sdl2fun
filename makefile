CXX = g++
CONFIG ?= Debug
CXXFLAGS_Debug = -g -O0 -Wall -std=c++17
CXXFLAGS_Release = -O2 -DNDEBUG -Wall -std=c++17
CXXFLAGS = $(CXXFLAGS_$(CONFIG))

BUILD_DIR = build
SRC_DIR = src
OBJ_DIR = $(BUILD_DIR)/objs
BIN_DIR = bin
ASSETS_DIR = assets

$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))
$(shell mkdir -p $(BIN_DIR)/$(ASSETS_DIR))

TARGET = $(BIN_DIR)/sdl2fun
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
ASSETS_SRC = $(shell find '$(ASSETS_DIR)' -type f -name '*')
ASSETS = $(ASSETS_SRC:%=$(BIN_DIR)/%)

build: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(ASSETS)

$(TARGET): $(OBJS) $(ASSETS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(shell sdl2-config --libs) -lGLEW -lGL

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(shell sdl2-config --cflags) -Iinclude

 $(BIN_DIR)/$(ASSETS_DIR)/%: $(ASSETS_DIR)/%
	cp $< $@

.PHONY: all clean build