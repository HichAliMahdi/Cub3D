/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_file_parser2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opetrovs <opetrovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:30:50 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/29 19:41:31 by opetrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	**expand_if_needed(char **lines, int count, int *capacity)
{
	if (count >= *capacity - 1)
	{
		*capacity *= 2;
		lines = expand_lines_array(lines, *capacity);
	}
	return (lines);
}

static char	**read_lines_loop(int fd, char **lines, int *count, int *capacity)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		lines = expand_if_needed(lines, *count, capacity);
		if (!lines)
			return (NULL);
		lines[(*count)++] = line;
		line = get_next_line(fd);
	}
	return (lines);
}

char	**read_all_lines(int fd, int *line_count)
{
	char	**lines;
	int		capacity;
	int		count;

	capacity = 50;
	count = 0;
	lines = init_lines_array(capacity);
	if (!lines)
		return (NULL);
	lines = read_lines_loop(fd, lines, &count, &capacity);
	if (!lines)
		return (NULL);
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

int	process_line_logic(char *trimmed, t_scene_config *config,
	int *is_map)
{
	if (is_map_line(trimmed))
	{
		*is_map = 1;
		free(trimmed);
		return (0);
	}
	if (!process_scene_element(trimmed, config))
	{
		free(trimmed);
		return (-1);
	}
	free(trimmed);
	return (0);
}
