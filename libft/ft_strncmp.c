/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:04:33 by hali-mah          #+#    #+#             */
/*   Updated: 2024/10/11 13:07:42 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	nbs1;
	unsigned char	nbs2;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		nbs1 = (unsigned char)s1[i];
		nbs2 = (unsigned char)s2[i];
		if (nbs1 != nbs2)
			return (nbs1 - nbs2);
		i++;
	}
	return (0);
}
