/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:01:37 by hali-mah          #+#    #+#             */
/*   Updated: 2025/07/01 12:51:48 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_mapinfo
{
	char	**map;
	bool	**visited;
	int		width;
	int		height;
}	t_mapinfo;

bool	**alloc_visited(int w, int h);
void	free_visited(bool **v, int h);
bool	find_player(char **map, int *x, int *y);
bool	is_valid_map_char(char c);
int		count_player_starts(char **map);
int		get_map_dimensions(char **map, int *width, int *height);
bool	perform_flood(char **map, int w, int h);
bool	is_map_enclosed(char **map);
bool	is_walkable(char c);
bool	check_boundary(t_mapinfo *info, int x, int y, char c);
char	get_map_char(char **map, int x, int y);
bool	flood_fill(t_mapinfo *info, int x, int y);
char	**parse_map(const char *filename);
void	free_map_lines(char **map, int count);
bool	resize_map(char ***map, int *cap, int lines);
bool	validate_map(char **map);
void	free_map(char **map);
bool	has_cub_extension(const char *filename);
bool	validate_file_extension(const char *filename);

#endif