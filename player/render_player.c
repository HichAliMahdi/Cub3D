/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:23:12 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 17:31:01 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_player(t_game *game)
{
	int	screen_x;
	int	screen_y;
	int	size;

	if (!game->textures->player)
		return ;
	screen_x = game->player.pos_x * TILE_SIZE - game->player.size / 2;
	screen_y = game->player.pos_y * TILE_SIZE - game->player.size / 2;
	size = game->player.size;
	mlx_image_to_window(game->mlx, game->textures->player, screen_x, screen_y);
}
