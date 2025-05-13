/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:52:56 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 18:05:41 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Perform Digital Differential Analysis (DDA) algorithm to find the wall
 */
void	perform_dda(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_x < 0)
			ray->hit = 1;
		else if (!game->map[ray->map_y] || !game->map[ray->map_y][ray->map_x])
			ray->hit = 1;
		else if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
