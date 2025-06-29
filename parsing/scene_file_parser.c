/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_file_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opetrovs <opetrovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:30:50 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/29 20:44:59 by opetrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
			|| line[i] == ' ')
			i++;
		else if (line[i] == '\n')
			break ;
		else
			return (false);
	}
	return (i > 0);
}

char	**init_lines_array(int capacity)
{
	char	**lines;

	lines = malloc(sizeof(char *) * capacity);
	return (lines);
}

char	**expand_lines_array(char **lines, int new_capacity)
{
	char	**new_lines;

	new_lines = realloc(lines, sizeof(char *) * new_capacity);
	return (new_lines);
}
