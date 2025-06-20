/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:31:41 by hali-mah          #+#    #+#             */
/*   Updated: 2024/10/11 13:07:36 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		length1;
	int		length2;

	length1 = ft_strlen(s1);
	length2 = ft_strlen(s2);
	newstr = malloc(length1 + length2 + 1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, length1 + 1);
	ft_strlcpy(newstr + length1, s2, length2 + 1);
	newstr[length1 + length2] = '\0';
	return (newstr);
}
