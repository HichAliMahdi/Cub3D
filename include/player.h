/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:20:03 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/28 07:15:07 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_game	t_game;
typedef struct s_player	t_player;

double	get_delta_time(void);
void	init_player_direction(t_player *player, char dir_char);
bool	init_player(t_game *game);
void	move_player(t_game *game, double dir_x,
			double dir_y, double delta_time);
void	handle_player_movement(t_game *game, double delta_time);
void	rotate_player(t_player *player, double rotation);
bool	is_wall(t_game *game, double x, double y);
bool	is_wall_with_padding(t_game *game, double x, double y);
void	render_player(t_game *game);

#endif