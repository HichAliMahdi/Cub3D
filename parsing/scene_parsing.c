/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:30:27 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/04 16:30:30 by hali-mah         ###   ########.fr       */
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

bool	parse_color(char *line, t_color *color)
{
	char	**parts;
	char	**rgb;
	int		r, g, b;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1])
		return (false);
	rgb = ft_split(parts[1], ',');
	free_map(parts);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		if (rgb)
			free_map(rgb);
		return (false);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_map(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	color->r = r;
	color->g = g;
	color->b = b;
	return (true);
}

bool	parse_scene_element(char *line, t_scene_config *config)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !config->textures_set[0])
	{
		config->textures_set[0] = parse_texture_path(line, &config->north_texture);
		return (config->textures_set[0]);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && !config->textures_set[1])
	{
		config->textures_set[1] = parse_texture_path(line, &config->south_texture);
		return (config->textures_set[1]);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0 && !config->textures_set[2])
	{
		config->textures_set[2] = parse_texture_path(line, &config->west_texture);
		return (config->textures_set[2]);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && !config->textures_set[3])
	{
		config->textures_set[3] = parse_texture_path(line, &config->east_texture);
		return (config->textures_set[3]);
	}
	else if (ft_strncmp(line, "F ", 2) == 0 && !config->floor_set)
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

bool	validate_scene_config(t_scene_config *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!config->textures_set[i])
		{
			fprintf(stderr, "Error\nMissing texture configuration\n");
			return (false);
		}
		i++;
	}
	if (!config->floor_set)
	{
		fprintf(stderr, "Error\nMissing floor color configuration\n");
		return (false);
	}
	if (!config->ceiling_set)
	{
		fprintf(stderr, "Error\nMissing ceiling color configuration\n");
		return (false);
	}
	return (true);
}

void	free_scene_config(t_scene_config *config)
{
	if (config->north_texture)
		free(config->north_texture);
	if (config->south_texture)
		free(config->south_texture);
	if (config->west_texture)
		free(config->west_texture);
	if (config->east_texture)
		free(config->east_texture);
	ft_memset(config, 0, sizeof(t_scene_config));
}
