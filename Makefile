# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opetrovs <opetrovs@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 16:40:57 by hali-mah          #+#    #+#              #
#    Updated: 2025/06/25 08:52:50 by opetrovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# # Compiler and flags
# CC      = cc
# CFLAGS  = -Wall -Wextra -Werror -Ilibft -IMLX42/include

# # Directories
# SRCDIR        = .
# MAPDIR        = map
# PARSEDIR      = parsing
# PLAYERDIR     = player
# RAYCASTINGDIR = raycasting
# MLX_DIR       = MLX42
# BUILD_DIR     = $(MLX_DIR)/build

# # Source files
# SRC     = main.c rendering.c get_next_line.c game_init.c utils.c \
#           $(MAPDIR)/map_parsing.c $(MAPDIR)/map_utils.c \
#           $(MAPDIR)/map_validation.c $(MAPDIR)/map_edges.c \
#           $(MAPDIR)/map_allocations.c $(MAPDIR)/map_check.c \
#           $(MAPDIR)/map_enclosure.c \
#           $(PLAYERDIR)/init_player.c $(PLAYERDIR)/move_player.c \
#           $(PLAYERDIR)/player_utils.c $(PLAYERDIR)/render_player.c \
#           $(PLAYERDIR)/rotate_player.c \
#           $(RAYCASTINGDIR)/raycasting_dda.c $(RAYCASTINGDIR)/raycasting_draw.c \
#           $(RAYCASTINGDIR)/raycasting_init.c $(RAYCASTINGDIR)/raycasting.c \
#           $(PARSEDIR)/scene_file_parser.c $(PARSEDIR)/scene_parsing.c

# OBJ     = $(SRC:.c=.o)

# # Output
# NAME    = cub3D

# # Libraries
# LIBFT   = libft/libft.a
# MLX_LIB = $(BUILD_DIR)/libmlx42.a

# # Frameworks and system libs
# LIBS    = -lglfw -ldl -framework OpenGL -framework Cocoa -pthread -lm

# # Rules
# all: $(NAME)

# $(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
# 	$(CC) $(OBJ) $(LIBFT) $(MLX_LIB) $(CFLAGS) $(LIBS) -o $(NAME)

# $(LIBFT):
# 	$(MAKE) -C libft

# $(MLX_LIB):
# 	git submodule update --init --recursive
# 	cmake -B $(BUILD_DIR) -S $(MLX_DIR)
# 	cmake --build $(BUILD_DIR)

# clean:
# 	$(MAKE) -C libft clean
# 	rm -f $(OBJ)

# fclean: clean
# 	$(MAKE) -C libft fclean
# 	rm -f $(NAME)
# 	rm -rf $(BUILD_DIR)

# re: fclean all

# .PHONY: all clean fclean re

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -IMLX42/include -I$(GLFW_INC)

# Directories
SRCDIR = .
MAPDIR = map
PARSEDIR = parsing
PLAYERDIR = player
RAYCASTINGDIR = raycasting
MLX_DIR = MLX42
BUILD_DIR = build
MLX_BUILD_DIR = $(MLX_DIR)/build

# GLFW paths (from Homebrew)
GLFW_PREFIX := $(shell brew --prefix glfw)
GLFW_INC := $(GLFW_PREFIX)/include
GLFW_LIB := $(GLFW_PREFIX)/lib

# Source files
SRC = main.c rendering.c get_next_line.c game_init.c utils.c \
	$(MAPDIR)/map_parsing.c $(MAPDIR)/map_utils.c \
	$(MAPDIR)/map_validation.c $(MAPDIR)/map_edges.c \
	$(MAPDIR)/map_allocations.c $(MAPDIR)/map_check.c \
	$(MAPDIR)/map_enclosure.c \
	$(PLAYERDIR)/init_player.c $(PLAYERDIR)/move_player.c \
	$(PLAYERDIR)/player_utils.c $(PLAYERDIR)/render_player.c \
	$(PLAYERDIR)/rotate_player.c \
	$(RAYCASTINGDIR)/raycasting_dda.c $(RAYCASTINGDIR)/raycasting_draw.c \
	$(RAYCASTINGDIR)/raycasting_init.c $(RAYCASTINGDIR)/raycasting.c \
	$(PARSEDIR)/scene_file_parser.c $(PARSEDIR)/scene_parsing.c

# Object files (in build directory)
OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))

# Output
NAME = cub3D

# Libraries
LIBFT = libft/libft.a
MLX_LIB = $(MLX_BUILD_DIR)/libmlx42.a

# Frameworks and system libs
LIBS = -L$(GLFW_LIB) -lglfw -ldl -framework OpenGL -framework Cocoa -pthread -lm

# Default target
all: $(NAME)

# Create build directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(MAPDIR)
	@mkdir -p $(BUILD_DIR)/$(PARSEDIR)
	@mkdir -p $(BUILD_DIR)/$(PLAYERDIR)
	@mkdir -p $(BUILD_DIR)/$(RAYCASTINGDIR)

# Link final binary
$(NAME): $(BUILD_DIR) $(OBJ) $(LIBFT) $(MLX_LIB)
	@echo "Linking $(NAME)..."
	$(CC) $(OBJ) $(LIBFT) $(MLX_LIB) $(LIBS) -o $(NAME)
	@echo "✅ $(NAME) created successfully!"

# Compile source files to object files in build folder
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C libft

# Build MLX42
$(MLX_LIB):
	@echo "Building MLX42..."
	@git submodule update --init --recursive
	@cmake -B $(MLX_BUILD_DIR) -S $(MLX_DIR)
	@cmake --build $(MLX_BUILD_DIR)

# Clean object files
clean:
	@echo "Cleaning object files..."
	@$(MAKE) -C libft clean
	@rm -rf $(BUILD_DIR)

# Full clean
fclean: clean
	@echo "Full clean..."
	@$(MAKE) -C libft fclean
	@rm -f $(NAME)
	@rm -rf $(MLX_BUILD_DIR)

# Rebuild everything
re: fclean all

# Debug target to check variables
debug:
	@echo "Source files: $(SRC)"
	@echo "Object files: $(OBJ)"
	@echo "GLFW prefix: $(GLFW_PREFIX)"
	@echo "Build directory: $(BUILD_DIR)"
	@echo "MLX lib: $(MLX_LIB)"
	@echo "Libft: $(LIBFT)"

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build the project"
	@echo "  clean   - Remove object files"
	@echo "  fclean  - Remove all generated files"
	@echo "  re      - Rebuild everything"
	@echo "  debug   - Show debug information"
	@echo "  help    - Show this help"

.PHONY: all clean fclean re debug help
