/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:55:22 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 17:02:46 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	validate_chars(char **map)
{
	int	x;
	int	y;

	if (!map || !map[0])
		return (false);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_map_char(map[y][x]))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_map(char **map)
{
	int	player_count;

	if (!map || !map[0])
		return (false);
	if (!validate_chars(map))
		return (false);
	player_count = count_player_starts(map);
	if (player_count != 1)
		return (false);
	if (!is_map_enclosed(map))
		return (false);
	return (true);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}
