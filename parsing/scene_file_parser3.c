/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_file_parser3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:30:50 by hali-mah          #+#    #+#             */
/*   Updated: 2025/07/01 20:28:01 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**parse_map_from_lines(char **lines, int start_line)
{
	char	**map;
	int		i;
	int		map_lines;
	int		j;

	map_lines = count_map_lines(lines, start_line);
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
			if (!copy_map_line(map, lines, &j, i))
				return (NULL);
		}
		i++;
	}
	map[j] = NULL;
	return (map);
}

static bool	open_and_read_file(const char *filename, char ***lines,
	int *line_count)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error\nCannot open file: %s\n", filename);
		return (false);
	}
	*lines = read_all_lines(fd, line_count);
	close(fd);
	if (!*lines)
	{
		fprintf(stderr, "Error\nFailed to read file\n");
		return (false);
	}
	return (true);
}

static bool	validate_and_parse_map(char **lines, t_scene_config *config,
	char ***map)
{
	int	map_start;

	map_start = find_map_start(lines, config);
	if (map_start == -1)
	{
		free_map(lines);
		return (false);
	}
	if (!validate_scene_config(config))
	{
		free_map(lines);
		return (false);
	}
	*map = parse_map_from_lines(lines, map_start);
	free_map(lines);
	if (!*map)
	{
		fprintf(stderr, "Error\nFailed to parse map\n");
		return (false);
	}
	return (true);
}

bool	parse_scene_file(const char *filename, t_scene_config *config,
	char ***map)
{
	char	**lines;
	int		line_count;

	ft_memset(config, 0, sizeof(t_scene_config));
	if (!open_and_read_file(filename, &lines, &line_count))
		return (false);
	return (validate_and_parse_map(lines, config, map));
}
