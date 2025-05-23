/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_edges.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:51:40 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/23 22:13:49 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	perform_flood(char **map, int w, int h)
{
	t_mapinfo	info;
	int			x;
	int			y;
	bool		ok;

	if (!find_player(map, &x, &y))
		return (false);
	info.map = map;
	info.visited = alloc_visited(w, h);
	info.width = w;
	info.height = h;
	if (!info.visited)
		return (false);
	ok = flood_fill(&info, x, y);
	free_visited(info.visited, h);
	return (ok);
}

bool	is_map_enclosed(char **map)
{
	int	w;
	int	h;

	if (!get_map_dimensions(map, &w, &h))
		return (false);
	if (h < 3 || w < 3)
	{
		fprintf(stderr, "Map too small: height %d, width %d\n", h, w);
		return (false);
	}
	return (perform_flood(map, w, h));
}
