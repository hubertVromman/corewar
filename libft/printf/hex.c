/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 15:00:53 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 15:00:54 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		len_hintmax_t(uintmax_t n)
{
	return ((n / 16 ? 1 + len_hintmax_t(n / 16) : 1));
}

void	ft_hitoa_u(uintmax_t n, char *to_write, int length)
{
	int		count_pos;

	count_pos = 0;
	if (!length)
		return ;
	to_write[--length] = n % 16 + (n % 16 > 9 ? 87 : 48);
	while (n /= 16)
		to_write[--length] = n % 16 + (n % 16 > 9 ? 87 : 48);
}

int		hex_func(uintmax_t number, char *f, int w[2])
{
	char	*created;
	int		size;
	int		len;
	int		slen;

	if (w[1] != -1)
		f[2] = 0;
	len = len_hintmax_t(number);
	size = !number && !w[1] ? 0 : ft_max(len, w[1]);
	slen = size + (number && f[4] ? 2 : 0);
	size = ft_max(slen, w[0]);
	if (!(created = realloc_g_str(size * f[9])))
		return (end_conv_nothing(-1, f, NULL, 0));
	ft_hitoa_u(number, created + size - len, len);
	ft_memset(created, '0', trun(size - len));
	if (number && f[4])
		created[f[2] ? 1 : size - slen + 1] = 'x';
	if (f[3] && w[0] == size && ft_memcpy(created, created + size - slen, slen))
		ft_memset(&created[slen], ' ', size - slen);
	else if (f[2] && w[0] == size)
		ft_memset(created + slen - len, '0', size - slen);
	else if (w[0] == size)
		ft_memset(created, ' ', size - slen);
	return (end_conv_nothing(0, f, created, size));
}

void	ft_mhitoa_u(uintmax_t n, char *to_write, int length)
{
	int		count_pos;

	count_pos = 0;
	if (!length)
		return ;
	to_write[--length] = n % 16 + (n % 16 > 9 ? 55 : 48);
	while (n /= 16)
		to_write[--length] = n % 16 + (n % 16 > 9 ? 55 : 48);
}

int		mhex_func(uintmax_t number, char *f, int w[2])
{
	char	*created;
	int		size;
	int		len;
	int		slen;

	if (w[1] != -1)
		f[2] = 0;
	len = len_hintmax_t(number);
	size = !number && !w[1] ? 0 : ft_max(len, w[1]);
	slen = size + (number && f[4] ? 2 : 0);
	size = ft_max(slen, w[0]);
	if (!(created = realloc_g_str(size * f[9])))
		return (end_conv_nothing(-1, f, NULL, 0));
	ft_mhitoa_u(number, created + size - len, len);
	ft_memset(created, '0', trun(size - len));
	if (number && f[4])
		created[f[2] ? 1 : size - slen + 1] = 'X';
	if (f[3] && w[0] == size && ft_memcpy(created, created + size - slen, slen))
		ft_memset(&created[slen], ' ', size - slen);
	else if (f[2] && w[0] == size)
		ft_memset(created + slen - len, '0', size - slen);
	else if (w[0] == size)
		ft_memset(created, ' ', size - slen);
	return (end_conv_nothing(0, f, created, size));
}
