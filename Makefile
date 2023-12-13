PROJ = hello_world

SRC_DIR = ./src
PROJ_DIR := $(SRC_DIR)/$(PROJ)
SRCS := $(PROJ_DIR)/main.cxx

BUILD_DIR := ./build
OBJ_DIR := $(BUILD_DIR)/obj/$(PROJ)
OBJS = $(SRCS:$(PROJ_DIR)/%.cxx=$(OBJ_DIR)/%.o)

TARGET_DIR := $(BUILD_DIR)/target/$(PROJ)
TARGET := $(TARGET_DIR)/app

CXX = g++
ifeq ($(CXX), clang++)
	LDFLAGS = -lstdc++ -ldl -lm
endif

.PHONY: all clean debug release build

all: debug
debug: CXX_FLAGS=-std=c++17 -O0 -Wall -Wextra -Wpedantic -g -Wpointer-arith
release: CXX_FLAGS=-std=c++17 -Ofast -finline-functions -ffast-math -funroll-all-loops
debug release: clean build
build: $(TARGET)

$(TARGET): $(OBJS)
	@echo 'Linking $@ from $<'
	@echo '[Rule] $@: $<'
	mkdir -p $(dir $@)
	$(CXX) $< -o $@ $(LDFLAGS)

$(OBJS): $(SRCS)
	@echo 'Compiling $@ from $<'
	@echo '[Rule] $@: $<'
	mkdir -p $(dir $@)
	$(CXX) -c $(CXX_FLAGS) $(CPP_FLAGS) $< -o $@

clean: 
	@echo 'Cleaning $(OBJ_DIR) and $(TARGET_DIR)'
	rm -rf $(OBJ_DIR)
	rm -rf $(TARGET_DIR)

cleanall:
	@echo 'Cleaning all build directories'
	rm -rf $(BUILD_DIR)