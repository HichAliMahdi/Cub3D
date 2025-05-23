/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:06:51 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/23 22:07:09 by hali-mah         ###   ########.fr       */
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
	int	count;

	count = 0;
	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	get_map_dimensions(char **map, int *width, int *height)
{
	int	i;
	int	w;
	int	len;

	*height = 0;
	w = 0;
	i = 0;
	while (map && map[i])
	{
		len = ft_strlen(map[i]);
		if (len > w)
			w = len;
		i++;
	}
	*width = w;
	*height = i;
	return (i > 0 && w > 0);
}
