/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:51:46 by hali-mah          #+#    #+#             */
/*   Updated: 2024/10/11 13:07:45 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	length;

	length = ft_strlen(s);
	while (length > 0)
	{
		if (s[length] == (char)c)
			return ((char *)s + length);
		length--;
	}
	if (s[0] == (char)c)
		return ((char *)s);
	return (NULL);
}
