/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:41:35 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 19:23:38 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:41:35 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 17:17:37 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

mlx_image_t	*load_texture(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	// Print debug information
	printf("Attempting to load texture: %s\n", path);

	tex = mlx_load_png(path);
	if (!tex)
	{
		fprintf(stderr, "Failed to load texture: %s\n", path);
		return (NULL);
	}

	img = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);

	if (!img)
	{
		fprintf(stderr, "Failed to convert texture to image: %s\n", path);
		return (NULL);
	}

	return (img);
}

t_textures	*load_all_textures(mlx_t *mlx)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
	{
		fprintf(stderr, "Failed to allocate memory for textures\n");
		return (NULL);
	}

	// Ensure correct path to textures
	textures->wall = load_texture(mlx, "./textures/wall.png");
	if (!textures->wall)
	{
		fprintf(stderr, "Failed to load wall texture\n");
		free(textures);
		return (NULL);
	}

	textures->floor = load_texture(mlx, "./textures/floor.png");
	if (!textures->floor)
	{
		fprintf(stderr, "Failed to load floor texture\n");
		mlx_delete_image(mlx, textures->wall);
		free(textures);
		return (NULL);
	}

	// Initialize player texture to NULL for now
	textures->player = NULL;

	return (textures);
}
