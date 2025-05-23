/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_enclosure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:07:19 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/23 22:13:24 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	check_boundary(t_mapinfo *info, int x, int y, char c)
{
	if (x < 0 || y < 0 || x >= info->width || y >= info->height)
		return (true);
	if (c == ' ')
	{
		if (x == 0 || y == 0 || x == info->width - 1 || y == info->height - 1)
			return (true);
	}
	return (false);
}

char	get_map_char(char **map, int x, int y)
{
	if (y < 0 || x < 0)
		return (' ');
	if (!map[y] || x >= (int)ft_strlen(map[y]))
		return (' ');
	return (map[y][x]);
}

bool	flood_fill(t_mapinfo *info, int x, int y)
{
	char	c;

	if (x < 0 || y < 0 || x >= info->width || y >= info->height)
		return (false);
	if (info->visited[y][x])
		return (true);
	c = get_map_char(info->map, x, y);
	if (c == '1')
		return (true);
	if (check_boundary(info, x, y, c))
		return (false);
	if (!is_walkable(c) && c != ' ')
		return (true);
	info->visited[y][x] = true;
	if (!flood_fill(info, x + 1, y))
		return (false);
	if (!flood_fill(info, x - 1, y))
		return (false);
	if (!flood_fill(info, x, y + 1))
		return (false);
	if (!flood_fill(info, x, y - 1))
		return (false);
	return (true);
}
