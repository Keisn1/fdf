##
# Fdf
#
# @file
# @version 0.1

# CC := cc
# CFLAGS := -Wall -Wextra -Werror

# CXX := g++
# CXXFLAGS := -Wall -Wextra -Werror
# FSANITIZE := -fsanitize=address
# GTEST_LIBS := -lgtest -lgtest_main -pthread #for googletests

# SRC := src
# OBJ := obj
# BIN := bin
# TEST := test
# RUN := run

# LIBFT := -Llibft -ft

CC := cc
CFLAGS := -Wall -Wextra -Werror
SRC := src
OBJ := obj
BIN := bin
SRC_FILES := $(wildcard $(SRC)/*.c)
OBJ_FILES := $(SRC_FILES:$(SRC)/%.c=$(OBJ)/%.o)
INCLUDES := -Imlx_linux
LIBMX := -Lmlx_linux -lmlx -lXext -lX11

NAME := fdf

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LIBMX)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)  # Ensure the obj directory exists
	$(CC) $(CFLAGS) $(INCLUDES) $(FSANITIZE) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(BIN)/*
	rm -f fdf

re: fclean all

bear: $(NAME)

.PHONY: all bear

# end
