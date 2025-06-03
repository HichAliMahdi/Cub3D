/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:36:48 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/03 15:38:02 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

bool	initialize_game_struct(t_game *game, char *filename)
{
	int	i;

	ft_memset(game, 0, sizeof(t_game));
	game->map = parse_map(filename);
	if (!game->map)
		return (false);
	i = 0;
	while (game->map[i])
		i++;
	game->mlx = mlx_init(800, 600, "CUB3D", true);
	if (!game->mlx)
		return (free_map(game->map), false);
	game->screen_width = 800;
	game->screen_height = 600;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	return (true);
}

bool	finalize_game_init(t_game *game)
{
	game->textures = load_all_textures(game->mlx);
	if (!game->textures)
	{
		cleanup(game);
		return (false);
	}
	game->player.size = 32;
	if (!init_player(game))
	{
		cleanup(game);
		return (false);
	}
	return (true);
}

bool	init_game(t_game *game, char *filename)
{
	if (!initialize_game_struct(game, filename))
		return (false);
	if (!finalize_game_init(game))
		return (false);
	return (true);
}
