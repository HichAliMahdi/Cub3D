/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:41:35 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 19:17:35 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

mlx_image_t	*load_texture(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png(path);
	if (!tex)
		return (NULL);
	img = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
		return (NULL);
	return (img);
}

static void	free_textures(mlx_t *mlx, t_textures *tex)
{
	if (tex->wall)
		mlx_delete_image(mlx, tex->wall);
	if (tex->floor)
		mlx_delete_image(mlx, tex->floor);
	if (tex->player)
		mlx_delete_image(mlx, tex->player);
	if (tex->north)
		mlx_delete_image(mlx, tex->north);
	if (tex->south)
		mlx_delete_image(mlx, tex->south);
	if (tex->east)
		mlx_delete_image(mlx, tex->east);
	if (tex->west)
		mlx_delete_image(mlx, tex->west);
	if (tex->screen)
		mlx_delete_image(mlx, tex->screen);
	free(tex);
}

t_textures	*load_all_textures(mlx_t *mlx)
{
	t_textures	*tex;

	tex = malloc(sizeof(t_textures));
	if (!tex)
		return (NULL);
	ft_memset(tex, 0, sizeof(t_textures));
	tex->wall = load_texture(mlx, "./textures/wall.png");
	if (!tex->wall)
		return (free(tex), NULL);
	tex->floor = load_texture(mlx, "./textures/floor.png");
	if (!tex->floor)
		return (free_textures(mlx, tex), NULL);
	tex->north = load_texture(mlx, "./textures/north_wall.png");
	if (!tex->north)
		return (free_textures(mlx, tex), NULL);
	tex->south = load_texture(mlx, "./textures/south_wall.png");
	if (!tex->south)
		return (free_textures(mlx, tex), NULL);
	tex->east = load_texture(mlx, "./textures/east_wall.png");
	if (!tex->east)
		return (free_textures(mlx, tex), NULL);
	tex->west = load_texture(mlx, "./textures/west_wall.png");
	if (!tex->west)
		return (free_textures(mlx, tex), NULL);
	return (tex);
}

void	render_frame(t_game *game)
{
	if (game->textures->screen)
		mlx_delete_image(game->mlx, game->textures->screen);
	game->textures->screen = mlx_new_image(game->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->textures->screen)
		return ;
	mlx_image_to_window(game->mlx, game->textures->screen, 0, 0);
	cast_rays(game);
}
