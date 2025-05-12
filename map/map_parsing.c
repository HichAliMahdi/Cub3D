/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:58:07 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 19:28:34 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_map_lines(char **map, int count)
{
	int	i;

	if (!map)
		return ;

	i = 0;
	while (i < count)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

static bool	resize_map(char ***map, int *cap, int lines)
{
	char	**new_map;

	*cap *= 2;
	new_map = realloc(*map, sizeof(char *) * (*cap));
	if (!new_map)
	{
		fprintf(stderr, "Memory reallocation failed\n");
		free_map_lines(*map, lines);
		return (false);
	}
	*map = new_map;
	return (true);
}

static bool	read_lines(FILE *file, char ***map, int *lines)
{
	char	*line = NULL;
	size_t	len = 0;
	ssize_t	read;
	int		cap = 10;

	*lines = 0;
	*map = malloc(sizeof(char *) * cap);
	if (!*map)
	{
		fprintf(stderr, "Initial map memory allocation failed\n");
		return (false);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		// Skip empty lines
		if (read <= 1 || line[0] == '\n')
		{
			free(line);
			line = NULL;
			len = 0;
			continue;
		}

		// Remove newline
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		// Resize map if needed
		if (*lines >= cap - 1 && !resize_map(map, &cap, *lines))
		{
			free(line);
			return (false);
		}

		// Duplicate and store the line
		(*map)[*lines] = ft_strdup(line);
		if (!(*map)[*lines])
		{
			fprintf(stderr, "Line duplication failed\n");
			free(line);
			free_map_lines(*map, *lines);
			return (false);
		}

		(*lines)++;
		(*map)[*lines] = NULL;

		// Free and reset line
		free(line);
		line = NULL;
		len = 0;
	}

	// Free last line if not already freed
	free(line);

	// Check if we read any lines
	if (*lines == 0)
	{
		fprintf(stderr, "No valid lines found in the map file\n");
		free(*map);
		*map = NULL;
		return (false);
	}

	return (true);
}

char	**parse_map(const char *filename)
{
	FILE	*file;
	char	**map = NULL;
	int		lines = 0;

	// Open file with error checking
	file = fopen(filename, "r");
	if (!file)
	{
		fprintf(stderr, "Error: Cannot open map file %s\n", filename);
		return (NULL);
	}

	// Read lines from the file
	if (!read_lines(file, &map, &lines))
	{
		fclose(file);
		return (NULL);
	}

	// Close file
	fclose(file);

	// Validate the map
	if (!validate_map(map))
	{
		fprintf(stderr, "Map validation failed\n");
		free_map_lines(map, lines);
		return (NULL);
	}

	return (map);
}
