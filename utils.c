/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:34:25 by hali-mah          #+#    #+#             */
/*   Updated: 2025/07/01 20:20:23 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	free_textures(t_game *game)
{
	if (game->textures->wall)
		mlx_delete_image(game->mlx, game->textures->wall);
	if (game->textures->floor)
		mlx_delete_image(game->mlx, game->textures->floor);
	if (game->textures->player)
		mlx_delete_image(game->mlx, game->textures->player);
	if (game->textures->north)
		mlx_delete_image(game->mlx, game->textures->north);
	if (game->textures->south)
		mlx_delete_image(game->mlx, game->textures->south);
	if (game->textures->east)
		mlx_delete_image(game->mlx, game->textures->east);
	if (game->textures->west)
		mlx_delete_image(game->mlx, game->textures->west);
	if (game->textures->screen)
		mlx_delete_image(game->mlx, game->textures->screen);
	free(game->textures);
	game->textures = NULL;
}

void	cleanup(t_game *game)
{
	if (game->map)
	{
		free_map(game->map);
		game->map = NULL;
	}
	if (game->textures)
		free_textures(game);
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	free_scene_config(&game->config);
}

void	check_leaks(void)
{
	system("leaks cub3D");
}

/*
Add this to the main to check leaks
	atexit(check_leaks);
*/