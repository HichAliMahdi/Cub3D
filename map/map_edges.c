/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_edges.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:51:40 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 16:36:13 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

int	count_player_starts(char **map)
{
	int	x;
	int	y;
	int	player_count;

	if (!map || !map[0])
		return (0);
	player_count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				player_count++;
			x++;
		}
		y++;
	}
	return (player_count);
}

static bool	check_edges(char **map, int width, int height)
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		if (map[0][x] != '1' && map[0][x] != ' ')
			return (false);
		if (map[height - 1][x] != '1' && map[height - 1][x] != ' ')
			return (false);
		x++;
	}
	y = 0;
	while (y < height)
	{
		if (map[y][0] != '1' && map[y][0] != ' ')
			return (false);
		if (map[y][width - 1] != '1' && map[y][width - 1] != ' ')
			return (false);
		y++;
	}
	return (true);
}

static bool	check_interior(char **map, int width, int height)
{
	int	x;
	int	y;

	y = 1;
	while (y < height - 1)
	{
		x = 1;
		while (x < width - 1)
		{
			if (map[y][x] == '0' || map[y][x] == 'N'
				|| map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
					|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	is_map_enclosed(char **map)
{
	int	width;
	int	height;

	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	if (height < 3 || width < 3)
	{
		fprintf(stderr, "Map too small: height %d, width %d\n", height, width);
		return (false);
	}
	if (!check_edges(map, width, height))
		return (false);
	if (!check_interior(map, width, height))
		return (false);
	return (true);
}
