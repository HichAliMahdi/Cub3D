/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:01:37 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 16:26:15 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

void	free_map_lines(char **map, int count);
bool	resize_map(char ***map, int *cap, int lines);
bool	is_valid_map_char(char c);
int		count_player_starts(char **map);
bool	is_map_enclosed(char **map);
bool	validate_map(char **map);
char	**parse_map(const char *filename);
void	free_map(char **map);

#endif