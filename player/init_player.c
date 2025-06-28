/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:18:21 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/28 07:14:47 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player_direction(t_player *player, char dir_char)
{
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	if (dir_char == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (dir_char == 'S')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (dir_char == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	else if (dir_char == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
}

static void	set_player(t_game *game, int x, int y, char dir)
{
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;
	init_player_direction(&game->player, dir);
	game->player.move_speed = 3.0;
	game->player.rot_speed = 2.0;
	game->map[y][x] = '0';
}

bool	init_player(t_game *game)
{
	int		y;
	int		x;
	char	dir;

	if (!game->map)
		return (false);
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			dir = game->map[y][x];
			if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
			{
				set_player(game, x, y, dir);
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}
