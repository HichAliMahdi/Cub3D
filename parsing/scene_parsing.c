/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opetrovs <opetrovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:30:27 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/29 19:36:42 by opetrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	parse_texture_path(char *line, char **texture_path)
{
	char	*trimmed;
	char	**parts;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1])
	{
		if (parts)
			free_map(parts);
		return (false);
	}
	trimmed = ft_strtrim(parts[1], " \t\n");
	if (!trimmed)
	{
		free_map(parts);
		return (false);
	}
	*texture_path = ft_strdup(trimmed);
	free(trimmed);
	free_map(parts);
	return (*texture_path != NULL);
}

static bool	validate_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (false);
	if (g < 0 || g > 255)
		return (false);
	if (b < 0 || b > 255)
		return (false);
	return (true);
}

static bool	extract_rgb_values(char **rgb, int *r, int *g, int *b)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (false);
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	return (true);
}

bool	parse_color(char *line, t_color *color)
{
	char	**parts;
	char	**rgb;
	int		values[3];

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1])
		return (false);
	rgb = ft_split(parts[1], ',');
	free_map(parts);
	if (!extract_rgb_values(rgb, &values[0], &values[1], &values[2]))
	{
		if (rgb)
			free_map(rgb);
		return (false);
	}
	free_map(rgb);
	if (!validate_rgb_values(values[0], values[1], values[2]))
		return (false);
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
	return (true);
}

static bool	parse_texture_element(char *line, t_scene_config *config)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !config->textures_set[0])
	{
		config->textures_set[0] = parse_texture_path(line,
				&config->north_texture);
		return (config->textures_set[0]);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && !config->textures_set[1])
	{
		config->textures_set[1] = parse_texture_path(line,
				&config->south_texture);
		return (config->textures_set[1]);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0 && !config->textures_set[2])
	{
		config->textures_set[2] = parse_texture_path(line,
				&config->west_texture);
		return (config->textures_set[2]);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && !config->textures_set[3])
	{
		config->textures_set[3] = parse_texture_path(line,
				&config->east_texture);
		return (config->textures_set[3]);
	}
	return (false);
}

static bool	parse_color_element(char *line, t_scene_config *config)
{
	if (ft_strncmp(line, "F ", 2) == 0 && !config->floor_set)
	{
		config->floor_set = parse_color(line, &config->floor_color);
		return (config->floor_set);
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !config->ceiling_set)
	{
		config->ceiling_set = parse_color(line, &config->ceiling_color);
		return (config->ceiling_set);
	}
	return (false);
}
