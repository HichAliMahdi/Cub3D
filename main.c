/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:21:30 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/12 19:29:34 by hali-mah         ###   ########.fr       */
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

void	cleanup(t_game *game)
{
	printf("Starting cleanup...\n");

	if (game->map)
	{
		printf("Freeing map\n");
		free_map(game->map);
		game->map = NULL;
	}
	
	if (game->textures)
	{
		printf("Cleaning up textures\n");
		if (game->textures->wall)
		{
			printf("Deleting wall texture\n");
			mlx_delete_image(game->mlx, game->textures->wall);
		}
		if (game->textures->floor)
		{
			printf("Deleting floor texture\n");
			mlx_delete_image(game->mlx, game->textures->floor);
		}
		free(game->textures);
		game->textures = NULL;
	}
	
	if (game->mlx)
	{
		printf("Terminating MLX\n");
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}

	printf("Cleanup complete\n");
}

static bool	init_game(t_game *game, char *filename)
{
	// Zero out the game structure
	printf("Initializing game with map file: %s\n", filename);
	memset(game, 0, sizeof(t_game));

	// Parse the map first
	game->map = parse_map(filename);
	if (!game->map)
	{
		fprintf(stderr, "Failed to parse map file: %s\n", filename);
		return (false);
	}

	// Print map details for debugging
	printf("Map parsed successfully\n");
	for (int i = 0; game->map[i]; i++)
		printf("Map line %d: %s\n", i, game->map[i]);

	// Initialize MLX
	printf("Initializing MLX\n");
	game->mlx = mlx_init(800, 600, "CUB3D", true);
	if (!game->mlx)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		free_map(game->map);
		return (false);
	}

	// Load textures
	printf("Loading textures\n");
	game->textures = load_all_textures(game->mlx);
	if (!game->textures)
	{
		fprintf(stderr, "Failed to load textures\n");
		cleanup(game);
		return (false);
	}

	printf("Game initialization complete\n");
	return (true);
}

static void	run_game(t_game *game)
{
	printf("Running game\n");

	// Set up key hook
	mlx_key_hook(game->mlx, key_hook, game->mlx);
	
	// Display textures for debugging
	if (game->textures->wall)
	{
		printf("Displaying wall texture\n");
		if (mlx_image_to_window(game->mlx, game->textures->wall, 100, 100) < 0)
		{
			fprintf(stderr, "Failed to display wall texture\n");
		}
	}
	
	if (game->textures->floor)
	{
		printf("Displaying floor texture\n");
		if (mlx_image_to_window(game->mlx, game->textures->floor, 200, 100) < 0)
		{
			fprintf(stderr, "Failed to display floor texture\n");
		}
	}
	
	// Start the MLX loop
	printf("Starting MLX loop\n");
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	// Check command line arguments
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	// Print current working directory for debugging
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL) 
	{
		printf("Current working directory: %s\n", cwd);
	}

	// Initialize the game
	printf("Starting game initialization\n");
	if (!init_game(&game, argv[1]))
	{
		fprintf(stderr, "Game initialization failed\n");
		return (EXIT_FAILURE);
	}

	// Run the game
	run_game(&game);
	
	// Cleanup
	cleanup(&game);
	return (EXIT_SUCCESS);
}
