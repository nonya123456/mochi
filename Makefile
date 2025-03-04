CC ?= clang
CFLAGS := -Iinclude
COBJFLAGS := $(CFLAGS) -c
LDFLAGS := -Llib \
	-framework CoreVideo \
	-framework IOKit \
	-framework Cocoa \
	-framework GLUT \
	-framework OpenGL \
	-lraylib \
	-lflecs_static

BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src

TARGET_NAME := mochi
TARGET := $(BIN_PATH)/$(TARGET_NAME)

SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

CLEAN_LIST := $(TARGET) $(OBJ)

default: makedir all

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) -o $@ $<

.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: rebuild
rebuild: clean all

.PHONY: run
run: rebuild
	@$(TARGET)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)
