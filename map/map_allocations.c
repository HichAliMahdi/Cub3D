/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:08:14 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/23 22:08:17 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	**alloc_visited(int w, int h)
{
	bool	**v;
	int		i;
	int		j;

	v = malloc(sizeof(bool *) * h);
	if (!v)
		return (NULL);
	i = 0;
	while (i < h)
	{
		v[i] = malloc(sizeof(bool) * w);
		if (!v[i])
		{
			j = 0;
			while (j < i)
				free(v[j++]);
			free(v);
			return (NULL);
		}
		ft_memset(v[i], 0, sizeof(bool) * w);
		i++;
	}
	return (v);
}

void	free_visited(bool **v, int h)
{
	int	i;

	if (!v)
		return ;
	i = 0;
	while (i < h)
	{
		free(v[i]);
		i++;
	}
	free(v);
}

bool	find_player(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				*x = j;
				*y = i;
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}
