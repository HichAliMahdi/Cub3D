/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:21:30 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/20 15:36:44 by hali-mah         ###   ########.fr       */
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

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->screen_width = width;
	game->screen_height = height;
	if (game->textures->screen)
		mlx_delete_image(game->mlx, game->textures->screen);
	game->textures->screen = mlx_new_image(game->mlx, width, height);
	if (game->textures->screen)
		mlx_image_to_window(game->mlx, game->textures->screen, 0, 0);
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

	atexit(check_leaks);
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
