/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:48:23 by hali-mah          #+#    #+#             */
/*   Updated: 2025/05/13 17:01:02 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static int	read_buffer(int fd, char *buffer, int *buffer_read, int *buffer_pos)
{
	*buffer_read = read(fd, buffer, BUFFER_SIZE);
	*buffer_pos = 0;
	return (*buffer_read);
}

static char	*append_char(char *line, int *size, int *allocated_size, char c)
{
	char	*new_line;
	int		i;

	if (*size >= *allocated_size - 1)
	{
		*allocated_size += BUFFER_SIZE;
		new_line = (char *)malloc(*allocated_size + 1);
		if (!new_line)
		{
			free(line);
			return (NULL);
		}
		i = 0;
		while (i < *size)
		{
			new_line[i] = line[i];
			i++;
		}
		free(line);
		line = new_line;
	}
	line[(*size)++] = c;
	return (line);
}

static char	*read_and_append(int fd, t_line *line, t_gnl *gnl)
{
	while (1)
	{
		if (gnl->buffer_pos >= gnl->buffer_read)
		{
			if (read_buffer(fd, gnl->buffer,
					&gnl->buffer_read, &gnl->buffer_pos) <= 0)
				break ;
		}
		line->str = append_char(line->str, &line->size,
				&line->allocated, gnl->buffer[gnl->buffer_pos++]);
		if (!line->str)
			return (NULL);
		if (line->str[line->size - 1] == '\n')
			break ;
	}
	return (line->str);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	t_line			line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line.allocated = BUFFER_SIZE;
	line.str = (char *)malloc(line.allocated + 1);
	if (!line.str)
		return (NULL);
	line.size = 0;
	line.str = read_and_append(fd, &line, &gnl);
	if (!line.str || line.size == 0)
	{
		free(line.str);
		return (NULL);
	}
	line.str[line.size] = '\0';
	return (line.str);
}
