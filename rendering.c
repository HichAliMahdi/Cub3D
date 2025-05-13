/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:41:35 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 17:44:11 by hali-mah         ###   ########.fr       */
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
	free(tex);
}

t_textures	*load_all_textures(mlx_t *mlx)
{
	t_textures	*tex;

	tex = malloc(sizeof(t_textures));
	if (!tex)
		return (NULL);
	tex->wall = load_texture(mlx, "./textures/wall.png");
	if (!tex->wall)
		return (free(tex), NULL);
	tex->floor = load_texture(mlx, "./textures/floor.png");
	if (!tex->floor)
		return (free_textures(mlx, tex), NULL);
	tex->player = load_texture(mlx, "./textures/player.png");
	if (!tex->player)
		return (free_textures(mlx, tex), NULL);
	return (tex);
}
