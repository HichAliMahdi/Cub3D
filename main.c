/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:21:30 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 19:24:07 by hali-mah         ###   ########.fr       */
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
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D", true);
	if (!game->mlx)
		return (free_map(game->map), false);
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
