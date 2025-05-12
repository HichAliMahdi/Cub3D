/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:55:22 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 19:28:57 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	validate_chars(char **map)
{
	int	x;
	int	y;

	if (!map || !map[0])
	{
		fprintf(stderr, "Invalid map: NULL or empty map\n");
		return (false);
	}

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_map_char(map[y][x]))
			{
				fprintf(stderr, "Invalid character '%c' at line %d, column %d\n", 
						map[y][x], y, x);
				return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_map(char **map)
{
	// Initial NULL check
	if (!map || !map[0])
	{
		fprintf(stderr, "Map validation failed: NULL or empty map\n");
		return (false);
	}

	// Validate map characters
	if (!validate_chars(map))
	{
		fprintf(stderr, "Map contains invalid characters\n");
		return (false);
	}

	// Check player start positions
	int player_count = count_player_starts(map);
	if (player_count != 1)
	{
		fprintf(stderr, "Invalid number of player start positions: %d (should be 1)\n", 
				player_count);
		return (false);
	}

	// Check map enclosure
	if (!is_map_enclosed(map))
	{
		fprintf(stderr, "Map is not properly enclosed\n");
		return (false);
	}

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
		i++;
	}
	free(map);
}
