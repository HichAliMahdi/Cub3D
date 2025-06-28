/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:23:14 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/28 07:11:07 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_player(t_player *player, double rotation)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rotation)
		- player->dir_y * sin(rotation);
	player->dir_y = old_dir_x * sin(rotation) + player->dir_y * cos(rotation);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rotation)
		- player->plane_y * sin(rotation);
	player->plane_y = old_plane_x * sin(rotation)
		+ player->plane_y * cos(rotation);
}
