/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:21:30 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 17:33:56 by hali-mah         ###   ########.fr       */
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
	game->mlx = mlx_init(800, 600, "CUB3D", true);
	if (!game->mlx)
	{
		free_map(game->map);
		return (false);
	}
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
	render_player(game);
}

static void	run_game(t_game *game)
{
	mlx_key_hook(game->mlx, key_hook, game->mlx);
	if (game->textures->wall)
		mlx_image_to_window(game->mlx, game->textures->wall, 100, 100);
	if (game->textures->floor)
		mlx_image_to_window(game->mlx, game->textures->floor, 200, 100);
	mlx_loop_hook(game->mlx, game_loop, game);
	printf("Starting MLX loop\n");
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (!init_game(&game, argv[1]))
	{
		cleanup(&game);
		return (EXIT_FAILURE);
	}
	run_game(&game);
	cleanup(&game);
	return (EXIT_SUCCESS);
}
