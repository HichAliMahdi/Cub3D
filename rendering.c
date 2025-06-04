/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:41:35 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/04 16:33:28 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

mlx_image_t	*load_texture(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	if (!path)
		return (NULL);
	tex = mlx_load_png(path);
	if (!tex)
	{
		fprintf(stderr, "Error\nFailed to load texture: %s\n", path);
		return (NULL);
	}
	img = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
	{
		fprintf(stderr, "Error\nFailed to convert texture to image: %s\n", path);
		return (NULL);
	}
	return (img);
}

static void	free_textures(mlx_t *mlx, t_textures *tex)
{
	if (tex->wall)
		mlx_delete_image(mlx, tex->wall);
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

t_textures	*load_all_textures(mlx_t *mlx, t_scene_config *config)
{
	t_textures	*tex;

	tex = malloc(sizeof(t_textures));
	if (!tex)
		return (NULL);
	ft_memset(tex, 0, sizeof(t_textures));
	tex->north = load_texture(mlx, config->north_texture);
	if (!tex->north)
		return (free_textures(mlx, tex), NULL);
	tex->south = load_texture(mlx, config->south_texture);
	if (!tex->south)
		return (free_textures(mlx, tex), NULL);
	tex->east = load_texture(mlx, config->east_texture);
	if (!tex->east)
		return (free_textures(mlx, tex), NULL);
	tex->west = load_texture(mlx, config->west_texture);
	if (!tex->west)
		return (free_textures(mlx, tex), NULL);
	tex->wall = load_texture(mlx, "./textures/wall.png");
	return (tex);
}

uint32_t	color_to_rgba(t_color color)
{
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | 0xFF);
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
