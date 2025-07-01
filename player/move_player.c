/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:23:03 by hali-mah          #+#    #+#             */
/*   Updated: 2025/07/01 11:18:32 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_delta_time(void)
{
	static double	last_time = 0;
	double			current_time;
	double			delta_time;

	current_time = mlx_get_time();
	if (last_time == 0)
		last_time = current_time;
	delta_time = current_time - last_time;
	last_time = current_time;
	if (delta_time > 0.016)
		delta_time = 0.016;
	return (delta_time);
}

void	move_player(t_game *game, double dir_x, double dir_y, double delta_time)
{
	double	new_x;
	double	new_y;
	double	speed;
	double	magnitude;

	magnitude = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (magnitude < 0.001)
		return ;
	dir_x /= magnitude;
	dir_y /= magnitude;
	speed = game->player.move_speed * delta_time;
	new_x = game->player.pos_x + dir_x * speed;
	new_y = game->player.pos_y + dir_y * speed;
	if (!is_wall_with_padding(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall_with_padding(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

static void	handle_wasd_keys(t_game *game, double *move_x, double *move_y)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		*move_x += game->player.dir_x;
		*move_y += game->player.dir_y;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		*move_x -= game->player.dir_x;
		*move_y -= game->player.dir_y;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		*move_x -= game->player.dir_y;
		*move_y += game->player.dir_x;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		*move_x += game->player.dir_y;
		*move_y -= game->player.dir_x;
	}
}

static double	handle_rotation_keys(t_game *game)
{
	double	rot_delta;

	rot_delta = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rot_delta -= game->player.rot_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rot_delta += game->player.rot_speed;
	return (rot_delta);
}

void	handle_player_movement(t_game *game, double delta_time)
{
	double	move_x;
	double	move_y;
	double	rot_delta;

	move_x = 0;
	move_y = 0;
	handle_wasd_keys(game, &move_x, &move_y);
	rot_delta = handle_rotation_keys(game);
	if (move_x != 0 || move_y != 0)
		move_player(game, move_x, move_y, delta_time);
	if (rot_delta != 0)
		rotate_player(&game->player, rot_delta * delta_time);
}
