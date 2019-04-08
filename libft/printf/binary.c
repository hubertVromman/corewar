/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:06:00 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/05 15:06:02 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		len_bintmax_t(uintmax_t n)
{
	return ((n / 2 ? 1 + len_bintmax_t(n / 2) : 1));
}

void	ft_bitoa_u(uintmax_t n, char *to_write, int length)
{
	int		count_pos;

	count_pos = 0;
	if (!length)
		return ;
	to_write[--length] = n % 2 + 48;
	while (n /= 2)
		to_write[--length] = n % 2 + 48;
}

int		binary_func(uintmax_t nb, char *f, int w[2])
{
	char	*created;
	int		size;
	int		len;
	int		slen;

	if (w[1] != -1)
		f[2] = 0;
	len = len_bintmax_t(nb);
	size = (!nb && !w[1]) ? 0 : ft_max(len, w[1]);
	slen = size;
	size = ft_max(slen, w[0]);
	if (!(created = realloc_g_str(size * f[9])))
		return (end_conv_nothing(-1, f, NULL, 0));
	ft_bitoa_u(nb, &created[size - len], len);
	ft_memset(created, '0', trun(size - len) + !nb && !w[1] ? 1 : 0);
	if (f[3] && w[0] == size && ft_memcpy(created, created + size - slen, slen))
		ft_memset(&created[slen], ' ', size - slen);
	else if (f[2] && w[0] == size)
		ft_memset(created + slen - len, '0', size - slen);
	else if (w[0] == size)
		ft_memset(created, ' ', size - slen);
	return (end_conv_nothing(0, f, created, size));
}
