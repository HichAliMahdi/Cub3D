/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:23:03 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/28 07:10:32 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// New delta time calculation function
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

// Updated move_player function with delta time
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
	if (!is_wall(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

// Updated movement handling with delta time
void	handle_player_movement(t_game *game, double delta_time)
{
	double	move_x = 0;
	double	move_y = 0;
	double	rot_delta = 0;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		move_x += game->player.dir_x;
		move_y += game->player.dir_y;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		move_x -= game->player.dir_x;
		move_y -= game->player.dir_y;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_x -= game->player.dir_y;
		move_y += game->player.dir_x;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_x += game->player.dir_y;
		move_y -= game->player.dir_x;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rot_delta -= game->player.rot_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rot_delta += game->player.rot_speed;
	if (move_x != 0 || move_y != 0)
		move_player(game, move_x, move_y, delta_time);
	if (rot_delta != 0)
		rotate_player(&game->player, rot_delta * delta_time);
}
