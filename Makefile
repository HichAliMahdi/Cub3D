# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 16:40:57 by hali-mah          #+#    #+#              #
#    Updated: 2025/06/20 15:54:51 by hali-mah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Ilibft -IMLX42/include

# Directories
SRCDIR        = .
MAPDIR        = map
PARSEDIR      = parsing
PLAYERDIR     = player
RAYCASTINGDIR = raycasting
MLX_DIR       = MLX42
BUILD_DIR     = $(MLX_DIR)/build

# Source files
SRC     = main.c rendering.c get_next_line.c game_init.c utils.c \
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

OBJ     = $(SRC:.c=.o)

# Output
NAME    = cub3D

# Libraries
LIBFT   = libft/libft.a
MLX_LIB = $(BUILD_DIR)/libmlx42.a

# Frameworks and system libs
LIBS    = -lglfw -ldl -framework OpenGL -framework Cocoa -pthread -lm

# Rules
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	$(CC) $(OBJ) $(LIBFT) $(MLX_LIB) $(CFLAGS) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MLX_LIB):
	git submodule update --init --recursive
	cmake -B $(BUILD_DIR) -S $(MLX_DIR)
	cmake --build $(BUILD_DIR)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)
	rm -rf $(BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re
