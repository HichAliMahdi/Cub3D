/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:19:47 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 16:54:45 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_textures
{
	mlx_image_t*	wall;
	mlx_image_t*	floor;
	mlx_image_t*	player;
}	t_textures;

int				main(void);
mlx_image_t*	load_texture(mlx_t* mlx, const char* path);
t_textures		load_all_textures(mlx_t* mlx);

#endif