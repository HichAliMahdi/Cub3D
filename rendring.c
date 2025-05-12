/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:41:35 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 16:44:00 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t*	load_texture(mlx_t* mlx, const char* path)
{
	mlx_texture_t*	tex;
	mlx_image_t*	img;

	tex = mlx_load_png(path);
	img = mlx_texture_to_image(mlx, tex);
	if (!tex)
	{
		fprintf(stderr, "Failed to load texture: %s\n", path);
		return (NULL);
	}
	mlx_delete_texture(tex);
	if (!img)
	{
		fprintf(stderr, "Failed to convert texture to image: %s\n", path);
	}

	return (img);
}
