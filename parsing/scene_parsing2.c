/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opetrovs <opetrovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:30:27 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/27 12:41:57 by opetrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	parse_scene_element(char *line, t_scene_config *config)
{
	if (parse_texture_element(line, config))
		return (true);
	if (parse_color_element(line, config))
		return (true);
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
