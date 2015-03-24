## Directories for include and src files
INC_DIR := include
SRC_DIR := src
## Directories to build files into
OBJ_DIR := obj
BIN_DIR := bin
## List of all c files to compile
C_FILES := $(wildcard $(SRC_DIR)/*.c)
INC_FILES := $(wildcard $(INC_DIR)/*.h)
## List of all object files to generate
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(C_FILES:$(SRC_DIR)/%.c=%.o))
## Compiler and linker flags and libraries to use
## CC := clang++
CC := gcc
CXXLIBS :=
LDLIBS := -lSDL2
CXXFLAGS := -I$(INC_DIR) `pkg-config --cflags gtk+-2.0`
LDFLAGS := `pkg-config --libs gtk+-2.0`
## Build files
## all: bin/BOBS
$(BIN_DIR)/BOBS: $(OBJ_FILES) | $(BIN_DIR)
	$(CC) -o $@ $^ $(LDFLAGS) -I$(INC_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CXXFLAGS)
$(OBJ_DIR):
	mkdir $(OBJ_DIR)
$(BIN_DIR):
	mkdir $(BIN_DIR)
clean:
	rm -rf obj
	rm -rf bin
## Include auto-generated dependencies rules
-include $(OBJ_FILES:.o=.d)