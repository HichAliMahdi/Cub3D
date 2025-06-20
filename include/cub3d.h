/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:19:47 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/20 15:37:12 by hali-mah         ###   ########.fr       */
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
# include "raycasting.h"
# include "player.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "map.h"

# define BUFFER_SIZE 42
# define TILE_SIZE 64
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_scene_config
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_color	floor_color;
	t_color	ceiling_color;
	bool	textures_set[4];
	bool	floor_set;
	bool	ceiling_set;
}	t_scene_config;

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
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*east;
	mlx_image_t	*west;
	mlx_image_t	*screen;
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
	mlx_t			*mlx;
	char			**map;
	t_textures		*textures;
	t_player		player;
	int				screen_width;
	int				screen_height;
	t_scene_config	config;
}	t_game;

int				main(int argc, char **argv);
mlx_image_t		*load_texture(mlx_t *mlx, const char *path);
t_textures		*load_all_textures(mlx_t *mlx, t_scene_config *config);
void			cleanup(t_game *game);
char			*get_next_line(int fd);
void			render_frame(t_game *game);
mlx_image_t		*select_texture(t_game *game, t_ray *ray);
bool			initialize_game_struct(t_game *game, char *filename);
bool			finalize_game_init(t_game *game);
bool			init_game(t_game *game, char *filename);
bool			parse_scene_file(const char *filename,
					t_scene_config *config, char ***map);
bool			parse_texture_path(char *line, char **texture_path);
bool			parse_color(char *line, t_color *color);
bool			parse_scene_element(char *line, t_scene_config *config);
bool			validate_scene_config(t_scene_config *config);
void			free_scene_config(t_scene_config *config);
void			check_leaks(void);

#endif