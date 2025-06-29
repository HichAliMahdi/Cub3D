/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_file_parser2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opetrovs <opetrovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:30:50 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/27 12:42:32 by opetrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	**read_all_lines(int fd, int *line_count)
{
	char	**lines;
	char	*line;
	int		capacity;
	int		count;

	capacity = 50;
	count = 0;
	lines = init_lines_array(capacity);
	if (!lines)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (count >= capacity - 1)
		{
			capacity *= 2;
			lines = expand_lines_array(lines, capacity);
			if (!lines)
				return (NULL);
		}
		lines[count++] = line;
		line = get_next_line(fd);
	}
	lines[count] = NULL;
	*line_count = count;
	return (lines);
}

static bool	process_scene_element(char *trimmed, t_scene_config *config)
{
	bool	parsed;

	parsed = parse_scene_element(trimmed, config);
	if (!parsed)
	{
		fprintf(stderr, "Error\nInvalid scene configuration: %s", trimmed);
		return (false);
	}
	return (true);
}

static int	find_map_start(char **lines, t_scene_config *config)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
		{
			i++;
			continue ;
		}
		trimmed = ft_strtrim(lines[i], " \t\n");
		if (!trimmed)
			return (-1);
		if (is_map_line(trimmed))
		{
			free(trimmed);
			return (i);
		}
		if (!process_scene_element(trimmed, config))
		{
			free(trimmed);
			return (-1);
		}
		free(trimmed);
		i++;
	}
	return (-1);
}

static int	count_map_lines(char **lines, int start_line)
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

static bool	copy_map_line(char **map, char **lines, int *j, int i)
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
