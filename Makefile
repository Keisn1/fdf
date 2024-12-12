##
# Fdf
#
# @file
# @version 0.1

# compilation
CC := cc
CFLAGS := -Wall -Wextra -Werror
FSANITIZE :=

# dirs
SRC_DIR := src
RUN_DIR := run
OBJ_DIR := obj
BIN_DIR := bin
BUILD_DIR := build

# libs
INCLUDES := -Iminilibx-linux -Ilibft -Iincludes
LIBFT := -Llibft -lft
LIBMLX := -Lminilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# targets
NAME := fdf

############ Rules ##################
all: $(NAME)

$(NAME): libft $(OBJ_FILES) $(RUN_DIR)/main.c
	$(CC) $(CFLAGS) $(OBJ_FILES) $(FSANITIZE) $(RUN_DIR)/main.c -o $(NAME) $(LIBMLX) $(LIBFT) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

############ PHONY ##################
clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)
	rm -f fdf

re: fclean all

test:
	cmake -S . -B build -DBUILD_TEST=ON && \
	cmake --build build && \
	./build/run_tests

compile_commands:
	cmake -S . -B build -DBUILD_TEST=ON -DBUILD_FDF=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && \
	rm -f compile_commands.json
	mv build/compile_commands.json ./compile_commands.json

libft:
	$(MAKE) -C libft

libft-re:
	$(MAKE) -C libft re

libft-clean:
	$(MAKE) -C libft clean

norminette:
	- norminette -R CheckForbiddenSourceHeader -R CheckDefine $(SRC_DIR)/
	- norminette -R CheckForbiddenSourceHeader -R CheckDefine $(INCLUDES)/

.PHONY: all clean fclean test libft test-obj-files

# end
