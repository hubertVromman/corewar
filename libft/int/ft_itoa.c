/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:09:44 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/02 15:09:46 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	len_int(int n)
{
	return ((n / 10 ? 1 + len_int(n / 10) : 1) + (!(n / 10) && n < 0 ? 1 : 0));
}

char		*ft_itoa(int n)
{
	int		count_pos;
	int		length;
	char	*to_return;

	length = len_int(n);
	count_pos = 0;
	to_return = ft_strnew(length);
	if (to_return)
	{
		if (n < 0)
		{
			to_return[count_pos++] = '-';
			if (n == -2147483648)
			{
				to_return[count_pos++] = '2';
				n += 2000000000;
			}
			n *= -1;
		}
		to_return[--length] = n % 10 + 48;
		while (n /= 10)
			to_return[--length] = n % 10 + 48;
	}
	return (to_return);
}
