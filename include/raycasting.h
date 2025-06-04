/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:52:08 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/04 16:44:48 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct s_game	t_game;
typedef struct s_player	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_ray;

void		perform_dda(t_game *game, t_ray *ray);
void		calculate_wall_data(t_ray *ray);
void		setup_texturing(t_game *game, t_ray *ray);
void		draw_walls(t_game *game, t_ray *ray, int x);
void		init_ray(t_game *game, t_ray *ray, int x);
void		clear_screen(t_game *game);
void		cast_rays(t_game *game);
#endif