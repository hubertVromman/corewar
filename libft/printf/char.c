/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:52:09 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 14:52:10 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		string_func(char *s, char *flag, int width[2], int fr)
{
	char	*created;
	int		size;
	int		len;

	if (!s)
		s = "(null)";
	len = (width[1] != -1) ? ft_min(width[1], ft_strlen(s)) : ft_strlen(s);
	size = ft_max(len, width[0]);
	if (!(created = realloc_g_str(size * flag[9])))
		return (end_conv_nothing(-1, flag, NULL, 0));
	ft_memcpy(created, s, len);
	if (!flag[3])
	{
		ft_memrcpy(created + size - len, created, len);
		ft_memset(created, (flag[2] ? '0' : ' '), size - len);
	}
	else
		ft_memset(created + len, ' ', size - len);
	if (fr)
		free(s);
	return (end_conv_nothing(0, flag, created, size));
}

int		char_func(unsigned char c, char *flag, int width[2])
{
	char	*created;
	int		size;
	int		len;

	len = 1;
	size = ft_max(len, width[0]);
	if (!(created = realloc_g_str(size * flag[9])))
		return (end_conv_nothing(-1, flag, NULL, 0));
	ft_memset(created, (flag[2] && !flag[3] ? '0' : ' '), size);
	created[(flag[3] ? 0 : size - 1)] = c;
	return (end_conv_nothing(0, flag, created, size));
}

int		rtring_func(char *s, char *flag, int width[2])
{
	int		count;
	char	*new_str;

	if (!s)
		s = "(null)";
	if (!(new_str = ft_strdup(s)))
		return (-1);
	count = -1;
	while (new_str[++count])
		new_str[count] = ft_isprint(s[count]) ? new_str[count] : '.';
	return (string_func(new_str, flag, width, 1));
}
