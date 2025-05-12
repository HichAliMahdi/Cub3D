/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:21:30 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 16:36:41 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t keydata, void* param)
{
	mlx_t*	mlx;

	mlx = (mlx_t*)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("ESC pressed. Exiting.\n");
		mlx_close_window(mlx);
	}
}

int main(void)
{
	mlx_t*	mlx;

	mlx = mlx_init(800, 600, "MLX42 Window", true);
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		return (EXIT_FAILURE);
	}
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
