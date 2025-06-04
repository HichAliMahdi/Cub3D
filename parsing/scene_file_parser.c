/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_file_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:30:50 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/04 16:45:34 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	is_empty_line(char *line)
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

static bool	is_map_line(char *line)
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
			break;
		else
			return (false);
	}
	return (i > 0);
}

static char	**read_all_lines(int fd, int *line_count)
{
	char	**lines;
	char	*line;
	int		capacity;
	int		count;

	capacity = 50;
	count = 0;
	lines = malloc(sizeof(char *) * capacity);
	if (!lines)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (count >= capacity - 1)
		{
			capacity *= 2;
			lines = realloc(lines, sizeof(char *) * capacity);
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

static int	find_map_start(char **lines, t_scene_config *config)
{
	int		i;
	char	*trimmed;
	bool	parsed;

	i = 0;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
		{
			i++;
			continue;
		}
		trimmed = ft_strtrim(lines[i], " \t\n");
		if (!trimmed)
			return (-1);
		if (is_map_line(trimmed))
		{
			free(trimmed);
			return (i);
		}
		parsed = parse_scene_element(trimmed, config);
		free(trimmed);
		if (!parsed)
		{
			fprintf(stderr, "Error\nInvalid scene configuration: %s", lines[i]);
			return (-1);
		}
		i++;
	}
	return (-1);
}

char	**parse_map_from_lines(char **lines, int start_line)
{
	char	**map;
	int		i;
	int		map_lines;
	int		j;

	map_lines = 0;
	i = start_line;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
			map_lines++;
		i++;
	}
	if (map_lines == 0)
		return (NULL);
	map = malloc(sizeof(char *) * (map_lines + 1));
	if (!map)
		return (NULL);
	j = 0;
	i = start_line;
	while (lines[i] && j < map_lines)
	{
		if (!is_empty_line(lines[i]))
		{
			map[j] = ft_strtrim(lines[i], "\n");
			if (!map[j])
			{
				free_map_lines(map, j);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	map[j] = NULL;
	return (map);
}

bool	parse_scene_file(const char *filename, t_scene_config *config, char ***map)
{
	int		fd;
	char	**lines;
	int		line_count;
	int		map_start;

	ft_memset(config, 0, sizeof(t_scene_config));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error\nCannot open file: %s\n", filename);
		return (false);
	}
	lines = read_all_lines(fd, &line_count);
	close(fd);
	if (!lines)
	{
		fprintf(stderr, "Error\nFailed to read file\n");
		return (false);
	}
	map_start = find_map_start(lines, config);
	if (map_start == -1 || !validate_scene_config(config))
	{
		free_map(lines);
		free_scene_config(config);
		return (false);
	}
	*map = parse_map_from_lines(lines, map_start);
	free_map(lines);
	if (!*map)
	{
		fprintf(stderr, "Error\nFailed to parse map\n");
		free_scene_config(config);
		return (false);
	}
	return (true);
}
