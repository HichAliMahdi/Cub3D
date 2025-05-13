/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:53:25 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 19:12:43 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Draw ceiling and floor colors
 */
static void	draw_screen_colors(t_game *game,
	uint32_t ceiling_color, uint32_t floor_color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
				mlx_put_pixel(game->textures->screen, x, y, ceiling_color);
			else
				mlx_put_pixel(game->textures->screen, x, y, floor_color);
			x++;
		}
		y++;
	}
}

/**
 * Clear the screen and prepare for rendering
 */
void	clear_screen(t_game *game)
{
	if (!game->textures->screen)
		return ;
	draw_screen_colors(game, 0x87CEEB, 0x8B4513);
}

/**
 * Main raycasting function that casts rays for each column
 * of the screen and renders the walls
 */
void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	if (!game->textures->screen)
		return ;
	clear_screen(game);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		calculate_wall_data(&ray);
		setup_texturing(game, &ray);
		draw_walls(game, &ray, x);
		x++;
	}
}
