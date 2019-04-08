/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 15:05:28 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 15:05:30 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		percent_func(char *f, int width[2])
{
	char	*created;
	int		size;
	int		count;

	size = ft_max(width[0], 1);
	if (!(created = realloc_g_str(size * f[9])))
		return (end_conv_nothing(-1, f, NULL, 0));
	count = -1;
	while (++count < width[0])
		created[count] = f[2] ? '0' : ' ';
	if (!f[3])
		created[trun(width[0] - 1)] = '%';
	else
		created[0] = '%';
	return (end_conv_nothing(0, f, created, size));
}

int		p_func(uintmax_t number, char *f, int width[2])
{
	char	*created;
	int		size;
	int		len;
	int		s_len;

	if (width[1] != -1)
		f[2] = 0;
	len = len_hintmax_t(number);
	len = (width[1] != -1 && !number ? width[1] : len);
	s_len = ft_max(len, width[1]) + 2;
	size = ft_max(s_len, width[0]);
	if (!(created = realloc_g_str(size * f[9])))
		return (end_conv_nothing(-1, f, NULL, 0));
	ft_memset(created, '0', size);
	ft_hitoa_u(number, f[3] && size > s_len ? created + 2
		: created + size - len, len);
	created[f[3] || f[2] ? 1 : size - s_len + 1] = 'x';
	if (!f[2])
		ft_memset(created + (f[3] ? s_len : 0), ' ', size - s_len);
	return (end_conv_nothing(0, f, created, size));
}

int		not_correct_flag(char *f, int width[2])
{
	char	*created;
	int		size;
	int		pos;

	pos = 6;
	while (f[pos] == 'h' || f[pos] == 'l' || f[pos] == 'z' || f[pos] == 'j')
		pos++;
	size = ft_max(width[0], f[pos] ? 1 : 0);
	if (!(created = realloc_g_str(size * f[9])))
		return (end_conv_nothing(-1, f, NULL, 0));
	ft_memset(created, (f[2] && !f[3] ? '0' : ' '), size);
	created[f[3] ? 0 : size - 1] = f[pos];
	return (end_conv_nothing(0, f, created, size));
}

int		output_file_func(va_list ap, char *f)
{
	int		fd;

	if (f[4])
	{
		g_outstr = va_arg(ap, char**);
		g_output = -1;
	}
	else
	{
		fd = va_arg(ap, int);
		if (fd != -1)
			g_output = fd;
	}
	free(f);
	return (0);
}
