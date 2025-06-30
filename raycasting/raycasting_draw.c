/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:53:35 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/30 09:41:45 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Select the appropriate texture based on the wall orientation
 */
mlx_image_t	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (game->textures->east);
		else
			return (game->textures->west);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (game->textures->south);
		else
			return (game->textures->north);
	}
}

/**
 * Get the color from the texture at the given coordinates
 */
static uint32_t	get_texture_color(t_game *game, t_ray *ray, int tex_y)
{
	uint32_t	color;
	mlx_image_t	*texture;
	uint8_t		*pixel;
	uint32_t	pos;

	texture = select_texture(game, ray);
	if (!texture)
		return (0);
	pos = (tex_y * texture->width + ray->tex_x) * 4;
	if (pos + 3 >= texture->width * texture->height * 4)
		return (0);
	pixel = &texture->pixels[pos];
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	return (color);
}

/**
 * Calculate wall distance and projection data
 */
void	calculate_wall_data(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

void	setup_texturing(t_game *game, t_ray *ray)
{
	mlx_image_t	*texture;
	double		scale_factor;

	texture = select_texture(game, ray);
	scale_factor = 0.5;
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	ray->step = scale_factor * texture->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2
			+ ray->line_height / 2) * ray->step;
}

/**
 * Draw the wall slice for the current column
 */
void	draw_walls(t_game *game, t_ray *ray, int x)
{
	int			y;
	uint32_t	color;
	int			tex_y;
	mlx_image_t	*texture;

	texture = select_texture(game, ray);
	if (!texture)
		return ;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos & (TEX_HEIGHT - 1);
		ray->tex_pos += ray->step;
		color = get_texture_color(game, ray, tex_y);
		mlx_put_pixel(game->textures->screen, x, y, color);
		y++;
	}
}
