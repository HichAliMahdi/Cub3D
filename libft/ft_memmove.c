/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:50:46 by hali-mah          #+#    #+#             */
/*   Updated: 2024/10/11 13:07:17 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst2;
	char	*src2;
	size_t	i;

	dst2 = (char *)dst;
	src2 = (char *)src;
	i = 0;
	if (src == NULL && dst == NULL)
		return (dst);
	if (src >= dst)
	{
		while (i < len)
		{
			dst2[i] = src2[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
		{
			dst2[len] = src2[len];
		}
	}
	return (dst);
}
