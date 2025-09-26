FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -lncurses
TARGET_DIR = ./build
SRC_DIRS = .

$(TARGET_DIR)/wm : wm.c
	mkdir -p $(TARGET_DIR)
	gcc -o $(TARGET_DIR)/wm wm.c ${FLAGS}