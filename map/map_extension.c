/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:46:55 by hali-mah          #+#    #+#             */
/*   Updated: 2025/07/01 12:53:15 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	has_cub_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strcmp(filename + len - 4, ".cub") == 0);
}

bool	validate_file_extension(const char *filename)
{
	if (!has_cub_extension(filename))
	{
		fprintf(stderr,
			"Error\nInvalid file extension. File must have .cub extension\n");
		return (false);
	}
	return (true);
}
