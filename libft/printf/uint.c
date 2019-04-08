/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:57:52 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 14:57:53 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		len_uintmax_t(uintmax_t n, char f)
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

void	ft_uitoa_u(uintmax_t n, char *to_write, int length, char f)
{
	int		count_pos;

	count_pos = 0;
	if (!length)
		return ;
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

int		unsigned_func(uintmax_t number, char *f, int w[2])
{
	char	*created;
	int		size;
	int		len;
	int		slen;

	if (w[1] != -1)
		f[2] = 0;
	len = len_uintmax_t(number, f[5]);
	size = ft_max(len, w[1]);
	if (!number && w[1] == 0)
		size = 0;
	slen = size;
	size = ft_max(size, w[0]);
	if (!(created = realloc_g_str(size * f[9])))
		return (end_conv_nothing(-1, f, NULL, 0));
	ft_uitoa_u(number, &created[size - len], len, f[5]);
	ft_memset(created, '0', trun(size - len));
	if (f[3] && w[0] == size && ft_memcpy(created, created + size - slen, slen))
		ft_memset(&created[slen], ' ', size - slen);
	else if (f[2] && w[0] == size)
		ft_memset(created + slen - len, '0', size - slen);
	else if (w[0] == size)
		ft_memset(created, ' ', size - slen);
	return (end_conv_nothing(0, f, created, size));
}
