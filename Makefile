.PHONY: build
.PHONY: run

APP_NAME = mochi
BUILD_DIR = build

build:
	@mkdir -p $(BUILD_DIR)
	@clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -Llib -Iinclude -lraylib main.c -o ./$(BUILD_DIR)/$(APP_NAME)

run: build
	@./$(BUILD_DIR)/$(APP_NAME)
