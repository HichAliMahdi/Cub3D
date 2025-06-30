# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 16:40:57 by hali-mah          #+#    #+#              #
#    Updated: 2025/06/30 20:02:01 by hali-mah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Detect architecture
UNAME_M := $(shell uname -m)

# Common settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -IMLX42/include

# Directories
SRCDIR = .
MAPDIR = map
PARSEDIR = parsing
PLAYERDIR = player
RAYCASTINGDIR = raycasting
MLX_DIR = MLX42
BUILD_DIR = build
MLX_BUILD_DIR = $(MLX_DIR)/build

# Architecture-specific settings
ifeq ($(UNAME_M),arm64)
	GLFW_PREFIX := $(shell brew --prefix glfw 2>/dev/null || echo "/opt/homebrew")
	GLFW_INC := $(GLFW_PREFIX)/include
	GLFW_LIB := $(GLFW_PREFIX)/lib
	CFLAGS += -I$(GLFW_INC)
	LIBS = -L$(GLFW_LIB) -lglfw -ldl -framework OpenGL -framework Cocoa -pthread -lm
else
	LIBS = -lglfw -ldl -framework OpenGL -framework Cocoa -pthread -lm
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

# Object files
OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))

# Output binary
NAME = cub3D

# Libraries
LIBFT = libft/libft.a
MLX_LIB = $(MLX_BUILD_DIR)/libmlx42.a

# Default target
all: check-tools check-submodule $(NAME)

# Create build directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(MAPDIR)
	@mkdir -p $(BUILD_DIR)/$(PARSEDIR)
	@mkdir -p $(BUILD_DIR)/$(PLAYERDIR)
	@mkdir -p $(BUILD_DIR)/$(RAYCASTINGDIR)

# Linking
$(NAME): $(BUILD_DIR) $(OBJ) $(LIBFT) $(MLX_LIB)
	@echo "🔗 Linking $(NAME)..."
	$(CC) $(OBJ) $(LIBFT) $(MLX_LIB) $(LIBS) -o $(NAME)
	@echo "✅ $(NAME) built successfully!"

# Compile source files
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "🛠️  Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	@echo "📦 Building libft..."
	@$(MAKE) -C libft

# Check tools
.PHONY: check-tools
check-tools:
	@command -v cmake >/dev/null 2>&1 || { echo "❌ cmake not found. Please install it."; exit 1; }
ifeq ($(UNAME_M),arm64)
	@command -v brew >/dev/null 2>&1 || { echo "❌ brew not found. Please install Homebrew."; exit 1; }
endif

# Submodule check
.PHONY: check-submodule
check-submodule:
	@echo "🔍 Checking MLX42 submodule..."
	@if [ ! -d "$(MLX_DIR)" ] || [ -z "$$(ls -A $(MLX_DIR) 2>/dev/null)" ]; then \
		echo "🚧 Initializing MLX42 submodule..."; \
		git submodule update --init --recursive || { \
			echo "❌ Submodule initialization failed."; exit 1; }; \
	else \
		echo "✅ MLX42 submodule is ready."; \
	fi

# MLX42 build
$(MLX_LIB): check-submodule
	@echo "🔧 Ensuring MLX42 build..."
	@if [ ! -f "$@" ]; then \
		$(MAKE) build-mlx42 || { echo "❌ MLX42 build failed."; exit 1; }; \
	fi

.PHONY: build-mlx42
build-mlx42:
	@echo "🧱 Building MLX42..."
	@mkdir -p $(MLX_BUILD_DIR)
	@cd $(MLX_DIR) && cmake -B build -S . && cmake --build build
	@echo "✅ MLX42 built successfully!"

# Manual bootstrap for first-time setup
.PHONY: bootstrap
bootstrap:
	@echo "🚀 Bootstrapping project..."
	git submodule update --init --recursive
	@$(MAKE) $(LIBFT)
	@$(MAKE) $(MLX_LIB)
	@echo "✅ Bootstrap complete. You can now run 'make'!"

# Clean
.PHONY: clean
clean:
	@echo "🧹 Cleaning object files..."
	@$(MAKE) -C libft clean
	@rm -rf $(BUILD_DIR)

# Full clean
.PHONY: fclean
fclean: clean
	@echo "🧨 Full clean..."
	@$(MAKE) -C libft fclean
	@rm -f $(NAME)
	@rm -rf $(MLX_BUILD_DIR)
	@rm -rf $(MLX_DIR)

# Rebuild all
.PHONY: re
re: fclean all

# Rebuild MLX
.PHONY: rebuild-mlx
rebuild-mlx:
	@echo "🔄 Rebuilding MLX42..."
	@rm -rf $(MLX_BUILD_DIR)
	@$(MAKE) $(MLX_LIB)

# Debug info
.PHONY: debug
debug:
	@echo "🔎 Debug Information:"
	@echo "Architecture: $(UNAME_M)"
	@echo "Source files: $(SRC)"
	@echo "Object files: $(OBJ)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LIBS: $(LIBS)"
ifeq ($(UNAME_M),arm64)
	@echo "GLFW prefix: $(GLFW_PREFIX)"
	@echo "GLFW include: $(GLFW_INC)"
	@echo "GLFW lib: $(GLFW_LIB)"
endif

# Help
.PHONY: help
help:
	@echo "📚 Available targets:"
	@echo "  all              - Build the project"
	@echo "  clean            - Remove object files"
	@echo "  fclean           - Remove all generated files"
	@echo "  re               - Rebuild everything"
	@echo "  bootstrap        - Run first-time setup (submodules + libs)"
	@echo "  rebuild-mlx      - Force rebuild MLX42"
	@echo "  debug            - Show debug information"
	@echo "  help             - Show this help"
