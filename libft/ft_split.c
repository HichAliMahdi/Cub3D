/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:45:14 by hali-mah          #+#    #+#             */
/*   Updated: 2024/10/11 13:07:28 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	**ft_allocate_memory(int size)
{
	return ((char **)malloc(sizeof(char *) * (size + 1)));
}

static int	ft_split_word(const char **s, char **new, int *index, char c)
{
	const char	*start;
	const char	*end;

	while (**s == c)
		(*s)++;
	start = *s;
	end = start;
	while (*end && *end != c)
		end++;
	if (end > start)
	{
		new[*index] = ft_substr(start, 0, end - start);
		if (!new[*index])
			return (0);
		(*index)++;
		*s = end;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		size;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	size = ft_count_words(s, c);
	new = ft_allocate_memory(size);
	if (!new)
		return (NULL);
	while (*s)
	{
		if (!ft_split_word(&s, new, &index, c))
		{
			while (index > 0)
				free(new[--index]);
			free(new);
			return (NULL);
		}
	}
	new[index] = NULL;
	return (new);
}
