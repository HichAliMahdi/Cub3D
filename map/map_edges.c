/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_edges.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:51:40 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 19:29:13 by hali-mah         ###   ########.fr       */
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

	// Check top and bottom rows
	x = 0;
	while (x < width)
	{
		// Top row
		if (map[0][x] != '1' && map[0][x] != ' ')
		{
			fprintf(stderr, "Invalid top edge at column %d: '%c'\n", x, map[0][x]);
			return (false);
		}

		// Bottom row
		if (map[height - 1][x] != '1' && map[height - 1][x] != ' ')
		{
			fprintf(stderr, "Invalid bottom edge at column %d: '%c'\n", x, map[height - 1][x]);
			return (false);
		}
		x++;
	}

	// Check left and right columns
	y = 0;
	while (y < height)
	{
		// Left column
		if (map[y][0] != '1' && map[y][0] != ' ')
		{
			fprintf(stderr, "Invalid left edge at row %d: '%c'\n", y, map[y][0]);
			return (false);
		}

		// Right column
		if (map[y][width - 1] != '1' && map[y][width - 1] != ' ')
		{
			fprintf(stderr, "Invalid right edge at row %d: '%c'\n", y, map[y][width - 1]);
			return (false);
		}
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
			// Check for player start or walkable space
			if (map[y][x] == '0' || map[y][x] == 'N'
				|| map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				// Check surrounding spaces
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
					|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
				{
					fprintf(stderr, "Map interior not enclosed at (%d, %d): '%c' has adjacent space\n", 
							y, x, map[y][x]);
					return (false);
				}
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

	// Count height
	height = 0;
	while (map[height])
		height++;

	// Get width from first row (assuming all rows have same width)
	width = ft_strlen(map[0]);

	// Validate map dimensions
	if (height < 3 || width < 3)
	{
		fprintf(stderr, "Map too small: height %d, width %d\n", height, width);
		return (false);
	}

	// Check map edges
	if (!check_edges(map, width, height))
		return (false);

	// Check map interior
	if (!check_interior(map, width, height))
		return (false);

	return (true);
}
