/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:34:25 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 17:34:43 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	cleanup(t_game *game)
{
	if (game->map)
	{
		free_map(game->map);
		game->map = NULL;
	}
	if (game->textures)
	{
		if (game->textures->wall)
			mlx_delete_image(game->mlx, game->textures->wall);
		if (game->textures->floor)
			mlx_delete_image(game->mlx, game->textures->floor);
		if (game->textures->player)
			mlx_delete_image(game->mlx, game->textures->player);
		free(game->textures);
		game->textures = NULL;
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
}
