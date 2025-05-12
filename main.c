/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:21:30 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 17:18:39 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("ESC pressed. Exiting.\n");
		mlx_close_window(mlx);
	}
}

int	main(void)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_textures		*tex;

	mlx = mlx_init(800, 600, "CUB3D", true);
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		return (EXIT_FAILURE);
	}
	img = load_texture(mlx, "textures/wall.png");
	tex = load_all_textures(mlx);
	if (!tex || !tex->wall || !tex->floor)
	{
		fprintf(stderr, "Failed to load one or more textures\n");
		mlx_terminate(mlx);
		free(tex);
		return (EXIT_FAILURE);
	}
	mlx_key_hook(mlx, key_hook, mlx);
	if (tex->wall)
		mlx_image_to_window(mlx, tex->wall, 100, 100);
	if (tex->floor)
		mlx_image_to_window(mlx, tex->floor, 200, 100);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free(tex);
	return (EXIT_SUCCESS);
}
