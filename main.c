/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:21:30 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 16:30:33 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	mlx_t*	mlx;

	mlx = mlx_init(800, 600, "MLX42 Window", true);
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		return (EXIT_FAILURE);
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
