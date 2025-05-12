/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:01:37 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 19:12:07 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

bool	is_valid_map_char(char c);
int		count_player_starts(char **map);
bool	is_map_enclosed(char **map);
bool	validate_map(char **map);
char	**parse_map(const char *filename);
void	free_map(char **map);

#endif