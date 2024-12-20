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
INCLUDES_DIR := includes
RUN_DIR := run
OBJ_DIR := obj
BIN_DIR := bin
BUILD_DIR := build
LIBFT_DIR := libft

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

$(NAME): $(LIBFT_DIR)/libft.a $(OBJ_FILES) $(RUN_DIR)/main.c
	$(CC) $(CFLAGS) $(OBJ_FILES) $(FSANITIZE) $(RUN_DIR)/main.c -o $(NAME) $(LIBMLX) $(LIBFT) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C libft

############ PHONY ##################
clean:
	$(MAKE) -C libft $@
	rm -f $(OBJ_FILES)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft $@
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)
	rm -f fdf

re: fclean all

libft:
	$(MAKE) -C libft

libft-re:
	$(MAKE) -C libft re

norminette:
	- norminette -R CheckForbiddenSourceHeader -R CheckDefine $(SRC_DIR)/
	- norminette -R CheckForbiddenSourceHeader -R CheckDefine $(INCLUDES_DIR)/

.PHONY: all clean fclean test libft test-obj-files

# end
