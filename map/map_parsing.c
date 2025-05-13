/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:58:07 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 17:13:51 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	init_map_buffer(char ***map, int *cap, int *lines)
{
	*cap = 10;
	*lines = 0;
	*map = malloc(sizeof(char *) * (*cap));
	if (!*map)
		return (false);
	return (true);
}

static bool	append_line_to_map(char *line, char ***map, int *lines, int *cap)
{
	if ((*lines) >= *cap - 1 && !resize_map(map, cap, *lines))
		return (false);
	(*map)[*lines] = ft_strdup(line);
	if (!(*map)[*lines])
	{
		free_map_lines(*map, *lines);
		return (false);
	}
	(*lines)++;
	(*map)[*lines] = NULL;
	return (true);
}

static bool	process_line(char *line, char ***map, int *lines, int *cap)
{
	if (line[0] == '\n')
		return (true);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (!append_line_to_map(line, map, lines, cap))
		return (false);
	return (true);
}

static bool	read_lines(int fd, char ***map, int *lines)
{
	char	*line;
	int		cap;
	bool	success;

	if (!init_map_buffer(map, &cap, lines))
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		success = process_line(line, map, lines, &cap);
		free(line);
		if (!success)
			return (false);
		line = get_next_line(fd);
	}
	if (*lines == 0)
	{
		free(*map);
		*map = NULL;
		return (false);
	}
	return (true);
}

char	**parse_map(const char *filename)
{
	int		fd;
	char	**map;
	int		lines;

	map = NULL;
	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!read_lines(fd, &map, &lines))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	if (!validate_map(map))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
