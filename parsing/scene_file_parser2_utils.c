/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_file_parser2_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opetrovs <opetrovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:45:00 by opetrovs          #+#    #+#             */
/*   Updated: 2025/06/29 21:04:19 by opetrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	process_config_line(char *line, t_scene_config *config, int *is_map)
{
	char	*trimmed;

	if (is_empty_line(line))
		return (0);
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (-1);
	if (is_map_line(trimmed))
	{
		*is_map = 1;
		free(trimmed);
		return (0);
	}
	if (!parse_scene_element(trimmed, config))
	{
		free(trimmed);
		return (-1);
	}
	free(trimmed);
	return (0);
}

int	find_map_start(char **lines, t_scene_config *config)
{
	int	i;
	int	is_map;
	int	result;

	i = 0;
	while (lines[i])
	{
		is_map = 0;
		result = process_config_line(lines[i], config, &is_map);
		if (result == -1)
			return (-1);
		if (is_map)
			return (i);
		i++;
	}
	return (-1);
}

int	count_map_lines(char **lines, int start_line)
{
	int	i;
	int	map_lines;

	map_lines = 0;
	i = start_line;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
			map_lines++;
		i++;
	}
	return (map_lines);
}

bool	copy_map_line(char **map, char **lines, int *j, int i)
{
	map[*j] = ft_strtrim(lines[i], "\n");
	if (!map[*j])
	{
		free_map_lines(map, *j);
		return (false);
	}
	(*j)++;
	return (true);
}
