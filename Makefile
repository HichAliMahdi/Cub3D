# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 16:40:57 by hali-mah          #+#    #+#              #
#    Updated: 2025/06/30 20:22:05 by hali-mah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Detect architecture
UNAME_M := $(shell uname -m)

# Common settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -g
LIBMLX = ./MLX42
MLX_URL = https://github.com/codam-coding-college/MLX42.git
INC = -I$(LIBMLX)/include -Ilibft

# Directories
SRCDIR = .
MAPDIR = map
PARSEDIR = parsing
PLAYERDIR = player
RAYCASTINGDIR = raycasting
BUILD_DIR = build

# Architecture-specific settings
ifeq ($(UNAME_M),arm64)
	# ARM MacBook (Apple Silicon) - using Homebrew
	GLFW_PREFIX := $(shell brew --prefix glfw 2>/dev/null || echo "/opt/homebrew")
	GLFW_INC := $(GLFW_PREFIX)/include
	GLFW_LIB := $(GLFW_PREFIX)/lib
	INC += -I$(GLFW_INC)
	LIBS = $(LIBMLX)/build/libmlx42.a -L$(GLFW_LIB) -lglfw -ldl -framework OpenGL -framework Cocoa -pthread -lm
else
	# Intel MacBook - using system libraries
	LIBS = $(LIBMLX)/build/libmlx42.a -lglfw -ldl -framework OpenGL -framework Cocoa -pthread -lm
endif

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
	$(PARSEDIR)/scene_file_parser.c $(PARSEDIR)/scene_file_parser2.c \
	$(PARSEDIR)/scene_file_parser2_utils.c $(PARSEDIR)/scene_parsing.c \
	$(PARSEDIR)/scene_file_parser3.c $(PARSEDIR)/scene_parsing2.c

# Object files (in build directory)
OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))

# Output
NAME = cub3D

# Libraries
LIBFT = libft/libft.a
MLX_LIB = $(LIBMLX)/build/libmlx42.a

# Default target
all: libmlx $(NAME)

# Create build directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(MAPDIR)
	@mkdir -p $(BUILD_DIR)/$(PARSEDIR)
	@mkdir -p $(BUILD_DIR)/$(PLAYERDIR)
	@mkdir -p $(BUILD_DIR)/$(RAYCASTINGDIR)

# Clone and build MLX42
libmlx:
	@echo "Checking if MLX42 library exists..."
	@if [ ! -f "$(MLX_LIB)" ]; then \
		if [ -d "$(LIBMLX)" ]; then \
			echo "MLX42 directory exists but library not built. Building..."; \
		else \
			echo "Cloning MLX42 from GitHub..."; \
			git clone $(MLX_URL) $(LIBMLX); \
		fi; \
		echo "Building MLX42..."; \
		cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	else \
		echo "MLX42 library already exists, skipping build."; \
	fi

# Link final binary
$(NAME): $(BUILD_DIR) $(OBJ) $(LIBFT) $(MLX_LIB)
	@echo "Linking $(NAME)..."
	$(CC) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "✅ $(NAME) created successfully!"

# Compile source files to object files in build folder
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Build libft
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C libft

# Clean object files
clean:
	@echo "Cleaning object files..."
	@$(MAKE) -C libft clean
	@rm -rf $(BUILD_DIR)
	@if [ -d "$(LIBMLX)/build" ]; then rm -rf $(LIBMLX)/build; fi

# Full clean
fclean: clean
	@echo "Full clean..."
	@$(MAKE) -C libft fclean
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)

# Clean MLX42 but keep the directory structure
clean-mlx:
	@echo "Cleaning MLX42 build files..."
	@rm -rf $(LIBMLX)/build

# Rebuild everything
re: fclean all

# Force rebuild MLX42
rebuild-mlx:
	@echo "Force rebuilding MLX42..."
	@rm -rf $(LIBMLX)
	@$(MAKE) libmlx

# Debug target to check variables and paths
debug:
	@echo "=== Debug Information ==="
	@echo "Architecture: $(UNAME_M)"
	@echo "Source files: $(SRC)"
	@echo "Object files: $(OBJ)"
	@echo "Build directory: $(BUILD_DIR)"
	@echo "MLX lib: $(MLX_LIB)"
	@echo "Libft: $(LIBFT)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "INC: $(INC)"
	@echo "LIBS: $(LIBS)"
ifeq ($(UNAME_M),arm64)
	@echo "GLFW prefix: $(GLFW_PREFIX)"
	@echo "GLFW include: $(GLFW_INC)"
	@echo "GLFW lib: $(GLFW_LIB)"
endif
	@echo "MLX42 directory exists: $$(if [ -d '$(LIBMLX)' ]; then echo 'YES'; else echo 'NO'; fi)"
	@echo "MLX42 header exists: $$(if [ -f '$(LIBMLX)/include/MLX42/MLX42.h' ]; then echo 'YES'; else echo 'NO'; fi)"
	@echo "MLX42 lib exists: $$(if [ -f '$(MLX_LIB)' ]; then echo 'YES'; else echo 'NO'; fi)"
	@echo "========================="

# Show help
help:
	@echo "Available targets:"
	@echo "  all              - Build the project"
	@echo "  clean            - Remove object files"
	@echo "  fclean           - Remove all generated files"
	@echo "  clean-mlx        - Clean MLX42 build files only"
	@echo "  re               - Rebuild everything"
	@echo "  rebuild-mlx      - Force rebuild MLX42"
	@echo "  libmlx           - Clone and build MLX42"
	@echo "  debug            - Show debug information"
	@echo "  help             - Show this help"

.PHONY: all clean fclean re debug help libmlx clean-mlx rebuild-mlx