/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:20:03 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 17:24:41 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

void	init_player_direction(t_player *player, char dir_char);
void	move_player(t_game *game, double dir_x, double dir_y);
void	handle_player_movement(t_game *game);

#endif