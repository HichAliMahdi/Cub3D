/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opetrovs <opetrovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:35:52 by hali-mah          #+#    #+#             */
/*   Updated: 2025/06/24 23:34:09 by opetrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_same(const char *hay, const char *needle, size_t i, size_t len)
{
	size_t	j;

	j = 0;
	while (hay[j] == needle[j] && i < len && hay[j] != '\0')
	{
		j++;
		i++;
	}
	if (j == ft_strlen(needle))
		return (j);
	return (-1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	ptvalue;
	char	*ptr;

	i = 0;
	ptr = (char *)haystack;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			ptvalue = i;
			if (is_same((haystack + i), needle, i, len) > 0)
			{
				ptr = (char *)haystack + ptvalue;
				return (ptr);
			}
			i = ptvalue;
		}
		i++;
	}
	return (NULL);
}
