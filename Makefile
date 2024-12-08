##
# Fdf
#
# @file
# @version 0.1

# compilation
CC := cc
CFLAGS := -Wall -Wextra -Werror

CXX := g++
CXXFLAGS := -Wall -Wextra -Werror
GTEST_LIBS := -lgtest -lgtest_main -pthread -lgmock #for googletests
FSANITIZE := -fsanitize=address

# dirs
SRC_DIR := src
RUN_DIR := run
OBJ_DIR := obj
BIN_DIR := bin
TEST_DIR := tests

# libs
INCLUDES := -Imlx_linux -Ilibft -Iincludes
LIBFT := -Llibft -lft
LIBMLX := -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_SRC_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES := $(TEST_SRC_FILES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# targets
TEST_TARGET := $(BIN_DIR)/run_tests
NAME := fdf

############ Rules ##################
all: $(NAME)

$(NAME): $(OBJ_FILES) $(RUN_DIR)/main.c
	$(CC) $(CFLAGS) $(OBJ_FILES) $(FSANITIZE) $(RUN_DIR)/main.c -o $(NAME) $(LIBMLX) $(LIBFT) $(INCLUDES)

$(TEST_TARGET): $(TEST_OBJ_FILES) $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(CFLAGS) $(FSANITIZE) $(TEST_OBJ_FILES) $(OBJ_FILES) -o $@ $(GTEST_LIBS) $(LIBFT) $(LIBMLX) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

############ PHONY ##################
clean:
	rm -f $(OBJ_FILES) $(TEST_OBJ_FILES)

fclean: clean
	rm -f $(BIN_DIR)/*
	rm -f fdf

re: fclean all

test: $(TEST_TARGET)
	- $(TEST_TARGET)

libft:
	$(MAKE) -C libft

libft-re:
	$(MAKE) -C libft re

libft-clean:
	$(MAKE) -C libft clean

bear: $(NAME) $(TEST_TARGET)

norminette:
	- norminette -R CheckForbiddenSourceHeader -R CheckDefine $(SRC_DIR)/
	- norminette -R CheckForbiddenSourceHeader -R CheckDefine $(INCLUDES)/

test-obj-files:
	@echo $(TEST_OBJ_FILES)

.PHONY: all clean fclean test libft test-obj-files

# end
