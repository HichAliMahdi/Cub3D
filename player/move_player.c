/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:23:03 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 17:24:45 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(t_game *game, double dir_x, double dir_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + dir_x * game->player.move_speed;
	new_y = game->player.pos_y + dir_y * game->player.move_speed;

	if (!is_wall(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	handle_player_movement(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, game->player.dir_x, game->player.dir_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, -game->player.dir_x, -game->player.dir_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player(game, -game->player.dir_y, game->player.dir_x);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game, game->player.dir_y, -game->player.dir_x);

	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(&game->player, -game->player.rot_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(&game->player, game->player.rot_speed);
}
