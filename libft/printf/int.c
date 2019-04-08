/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:55:13 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 14:55:14 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		len_intmax_t(intmax_t n, char f)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (n /= 10)
	{
		i++;
		if (f && !(i % 3))
			j++;
	}
	i++;
	return (i + j);
}

void	ft_itoa_u(intmax_t n, char *to_write, int length, char f)
{
	int		count_pos;

	count_pos = 0;
	if (!length)
		return ;
	if (n < 0)
	{
		if (n == INTMAX_MIN)
		{
			to_write[count_pos++] = INTMAX_MAX / (ft_pow(10, length - 1)) + '0';
			n += INTMAX_MAX - INTMAX_MAX % ft_pow(10, length - 1);
		}
		n *= -1;
	}
	to_write[--length] = n % 10 + 48;
	count_pos++;
	while (n /= 10)
	{
		if (f && !(count_pos % 3))
			to_write[--length] = ',';
		to_write[--length] = n % 10 + 48;
		count_pos++;
	}
}

int		signed_func(intmax_t number, char *f, int w[2])
{
	char	*new;
	int		size;
	int		len;
	int		slen;
	int		s;

	f[2] = (w[1] != -1) ? 0 : f[2];
	s = f[0] || f[1] || number < 0 ? 1 : 0;
	len = len_intmax_t(number, f[5]);
	slen = !number && !w[1] ? 0 : ft_max(len, w[1]) + s;
	size = ft_max(slen, w[0]);
	if (!(new = realloc_g_str(size * f[9])))
		return (end_conv_nothing(-1, f, NULL, 0));
	ft_itoa_u(number, new + size - len, len, f[5]);
	ft_memset(new, '0', trun(size - len));
	if (f[3] && w[0] == size && ft_memcpy(new + s, new + size - slen + s, slen))
		ft_memset(&new[slen], ' ', size - slen);
	else if (w[0] == size)
		ft_memset(new + (f[2] ? slen - len : 0), f[2] ? '0' : ' ', size - slen);
	if (number < 0)
		new[!(f[2] || f[3]) ? size - slen : 0] = '-';
	else if (s)
		new[!(f[2] || f[3]) ? size - slen : 0] = (f[1] ? '+' : ' ');
	return (end_conv_nothing(0, f, new, size));
}
