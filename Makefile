# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 16:40:57 by hali-mah          #+#    #+#              #
#    Updated: 2025/05/13 17:36:28 by hali-mah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Ilibft -IMLX42/include

# Directories
SRCDIR     = .
MAPDIR     = map
PLAYERDIR  = player
MLX_DIR    = MLX42
BUILD_DIR  = $(MLX_DIR)/build

# Source files
SRC     = main.c rendering.c get_next_line.c utils.c \
          $(MAPDIR)/map_parsing.c $(MAPDIR)/map_utils.c \
          $(MAPDIR)/map_validation.c $(MAPDIR)/map_edges.c \
		  $(PLAYERDIR)/init_player.c $(PLAYERDIR)/move_player.c \
		  $(PLAYERDIR)/player_utils.c $(PLAYERDIR)/render_player.c \
		  $(PLAYERDIR)/rotate_player.c

OBJ     = $(SRC:.c=.o)

# Output
NAME    = cub3d

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
	cmake -B $(BUILD_DIR) -S $(MLX_DIR)
	cmake --build $(BUILD_DIR)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re