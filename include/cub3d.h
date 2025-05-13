/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:19:47 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 17:28:28 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/param.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "map.h"
# include "player.h"

# define BUFFER_SIZE 42
# define TILE_SIZE 64

typedef struct s_gnl
{
	char	buffer[BUFFER_SIZE];
	int		buffer_read;
	int		buffer_pos;
}	t_gnl;

typedef struct s_line
{
	char	*str;
	int		size;
	int		allocated;
}	t_line;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_color;
	int		ceiling_color;
	t_map	map;
}	t_config;

typedef struct s_textures
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*player;
}	t_textures;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	int		size;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	char		**map;
	t_textures	*textures;
	t_player	player;
}	t_game;

int				main(int argc, char **argv);
mlx_image_t		*load_texture(mlx_t *mlx, const char *path);
t_textures		*load_all_textures(mlx_t *mlx);
void			cleanup(t_game *game);
char			*get_next_line(int fd);
#endif