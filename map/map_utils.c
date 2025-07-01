/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:25:14 by hali-mah          #+#    #+#             */
/*   Updated: 2025/07/01 20:18:38 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_map_lines(char **map, int count)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < count)
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
		i++;
	}
	free(map);
}

bool	resize_map(char ***map, int *cap, int lines)
{
	char	**new_map;
	int		i;

	*cap *= 2;
	new_map = malloc(sizeof(char *) * (*cap));
	if (!new_map)
	{
		free_map_lines(*map, lines);
		*map = NULL;
		return (false);
	}
	i = 0;
	while (i < lines)
	{
		new_map[i] = (*map)[i];
		i++;
	}
	while (i < *cap)
	{
		new_map[i] = NULL;
		i++;
	}
	free(*map);
	*map = new_map;
	return (true);
}
