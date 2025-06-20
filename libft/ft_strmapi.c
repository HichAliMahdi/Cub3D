/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:18:10 by hali-mah          #+#    #+#             */
/*   Updated: 2024/10/11 13:07:40 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const	*s, char (*f)(unsigned int, char))
{
	char	*neu;
	int		len;
	int		i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	neu = (char *)malloc(sizeof(char) * (len + 1));
	if (!neu)
		return (NULL);
	i = 0;
	while (i < len)
	{
		neu[i] = f(i, s[i]);
		i++;
	}
	neu[i] = '\0';
	return (neu);
}
