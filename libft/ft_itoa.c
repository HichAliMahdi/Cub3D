/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:58:35 by hali-mah          #+#    #+#             */
/*   Updated: 2024/10/11 13:06:49 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	get_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		if (n == -2147483648)
		{
			n++;
		}
		n = -n;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	num_cvt(char *str, unsigned int num, size_t len)
{
	str[len--] = '\0';
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	size_t			len;
	char			*str;
	unsigned int	num;

	len = get_len(n);
	if (n < 0)
		num = (unsigned int)(-n);
	else
		num = (unsigned int)n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	num_cvt(str, num, len);
	return (str);
}
