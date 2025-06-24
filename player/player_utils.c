/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opetrovs <opetrovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:23:10 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/23 08:14:21 by opetrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_x < 0)
		return (true);
	if (!game->map[map_y] || !game->map[map_y][map_x])
		return (true);
	return (game->map[map_y][map_x] == '1');
}

bool	is_wall_with_padding(t_game *game, double x, double y)
{
	double	padding;

	padding = 0.1;
	if (is_wall(game, x - padding, y - padding)
		|| is_wall(game, x + padding, y - padding)
		|| is_wall(game, x - padding, y + padding)
		|| is_wall(game, x + padding, y + padding))
		return (true);
	return (false);
}
