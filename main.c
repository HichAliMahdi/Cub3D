/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:21:30 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/03 15:34:52 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("ESC pressed. Exiting.\n");
		mlx_close_window(mlx);
	}
}

/* New resize callback function */
void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->screen_width = width;
	game->screen_height = height;
	
	/* Recreate the screen image with new dimensions */
	if (game->textures->screen)
		mlx_delete_image(game->mlx, game->textures->screen);
	
	game->textures->screen = mlx_new_image(game->mlx, width, height);
	if (game->textures->screen)
		mlx_image_to_window(game->mlx, game->textures->screen, 0, 0);
}

static bool	init_game(t_game *game, char *filename)
{
	int	i;

	ft_memset(game, 0, sizeof(t_game));
	game->map = parse_map(filename);
	if (!game->map)
		return (false);
	i = 0;
	while (game->map[i])
		i++;
	game->mlx = mlx_init(800, 600, "CUB3D", true);
	if (!game->mlx)
		return (free_map(game->map), false);
	game->screen_width = 800;
	game->screen_height = 600;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->textures = load_all_textures(game->mlx);
	if (!game->textures)
	{
		cleanup(game);
		return (false);
	}
	game->player.size = 32;
	if (!init_player(game))
	{
		cleanup(game);
		return (false);
	}
	return (true);
}

static void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_player_movement(game);
	render_frame(game);
	render_player(game);
}

static void	run_game(t_game *game)
{
	mlx_key_hook(game->mlx, key_hook, game->mlx);
	mlx_resize_hook(game->mlx, resize_hook, game);
	render_frame(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	printf("Starting Game\n");
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (!init_game(&game, argv[1]))
	{
		cleanup(&game);
		return (EXIT_FAILURE);
	}
	run_game(&game);
	cleanup(&game);
	return (EXIT_SUCCESS);
}
