# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opetrovs <opetrovs@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 16:40:57 by hali-mah          #+#    #+#              #
#    Updated: 2025/06/29 20:43:41 by opetrovs         ###   ########.fr        #
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
	# ARM MacBook (Apple Silicon) - using Homebrew
	GLFW_PREFIX := $(shell brew --prefix glfw 2>/dev/null || echo "/opt/homebrew")
	GLFW_INC := $(GLFW_PREFIX)/include
	GLFW_LIB := $(GLFW_PREFIX)/lib
	CFLAGS += -I$(GLFW_INC)
	LIBS = -L$(GLFW_LIB) -lglfw -ldl -framework OpenGL -framework Cocoa -pthread -lm
else
	# Intel MacBook - using system libraries
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
	$(PARSEDIR)/scene_file_parser3.c $(PARSEDIR)/scene_parsing2.c \


# Object files (in build directory)
OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))

# Output
NAME = cub3D

# Libraries
LIBFT = libft/libft.a
MLX_LIB = $(MLX_BUILD_DIR)/libmlx42.a

# Default target
all: check-submodule $(NAME)

# Create build directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(MAPDIR)
	@mkdir -p $(BUILD_DIR)/$(PARSEDIR)
	@mkdir -p $(BUILD_DIR)/$(PLAYERDIR)
	@mkdir -p $(BUILD_DIR)/$(RAYCASTINGDIR)

# Check if MLX42 submodule is initialized
.PHONY: check-submodule
check-submodule:
	@echo "Checking MLX42 submodule..."
	@if [ ! -d "$(MLX_DIR)/.git" ] || [ ! -f "$(MLX_DIR)/include/MLX42/MLX42.h" ]; then \
		echo "Initializing MLX42 submodule..."; \
		git submodule update --init --recursive || \
		(echo "❌ Failed to initialize submodule. Please run manually: git submodule update --init --recursive" && exit 1); \
		echo "✅ MLX42 submodule initialized successfully!"; \
	else \
		echo "✅ MLX42 submodule already initialized."; \
	fi

# Link final binary
$(NAME): $(BUILD_DIR) $(OBJ) $(LIBFT) $(MLX_LIB)
	@echo "Linking $(NAME)..."
	$(CC) $(OBJ) $(LIBFT) $(MLX_LIB) $(LIBS) -o $(NAME)
	@echo "✅ $(NAME) created successfully!"

# Compile source files to object files in build folder
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR) check-submodule
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C libft

# Build MLX42 with submodule check
$(MLX_LIB): check-submodule
	@echo "Building MLX42..."
	@if [ ! -d "$(MLX_BUILD_DIR)" ]; then \
		echo "Creating MLX42 build directory..."; \
		mkdir -p $(MLX_BUILD_DIR); \
	fi
	@echo "Running cmake configuration..."
	@cd $(MLX_DIR) && cmake -B build -S . || \
		(echo "CMake configuration failed. Check if cmake is installed." && exit 1)
	@echo "Building MLX42 library..."
	@cd $(MLX_DIR) && cmake --build build || \
		(echo "MLX42 build failed." && exit 1)
	@echo "✅ MLX42 built successfully!"

# Initialize submodules target (can be run manually)
init-submodules:
	@echo "🔄 Initializing git submodules..."
	git submodule update --init --recursive
	@echo "✅ Submodules initialized successfully!"

# Force update submodules
update-submodules: 
	@echo "🔄 Updating all submodules..."
	git submodule update --remote --recursive
	@echo "✅ Submodules updated successfully!"

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

# Force rebuild MLX42
rebuild-mlx:
	@echo "Force rebuilding MLX42..."
	@rm -rf $(MLX_BUILD_DIR)
	@$(MAKE) $(MLX_LIB)

# Debug target to check variables
debug:
	@echo "=== Debug Information ==="
	@echo "Architecture: $(UNAME_M)"
	@echo "Source files: $(SRC)"
	@echo "Object files: $(OBJ)"
	@echo "Build directory: $(BUILD_DIR)"
	@echo "MLX lib: $(MLX_LIB)"
	@echo "Libft: $(LIBFT)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LIBS: $(LIBS)"
ifeq ($(UNAME_M),arm64)
	@echo "GLFW prefix: $(GLFW_PREFIX)"
	@echo "GLFW include: $(GLFW_INC)"
	@echo "GLFW lib: $(GLFW_LIB)"
endif
	@echo "========================="

# Show help
help:
	@echo "Available targets:"
	@echo "  all              - Build the project"
	@echo "  clean            - Remove object files"
	@echo "  fclean           - Remove all generated files"
	@echo "  re               - Rebuild everything"
	@echo "  rebuild-mlx      - Force rebuild MLX42"
	@echo "  init-submodules  - Initialize git submodules manually"
	@echo "  update-submodules - Update git submodules to latest"
	@echo "  debug            - Show debug information"
	@echo "  help             - Show this help"

.PHONY: all clean fclean re debug help init-submodules update-submodules rebuild-mlx check-submodule
