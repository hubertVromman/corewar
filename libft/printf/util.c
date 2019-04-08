/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:47:01 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 14:47:03 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*realloc_g_str(int size)
{
	char	*tmp;

	tmp = g_str;
	if (size > 0)
	{
		if (!(g_str = (char *)malloc(sizeof(char) * (g_len + size + 1))))
		{
			free(tmp);
			return (NULL);
		}
		ft_memcpy(g_str, tmp, g_len);
		free(tmp);
		tmp = g_str + g_len;
		g_len += size;
		g_str[g_len] = 0;
	}
	return (tmp);
}

int		trun(int nb)
{
	return (nb < 0 ? 0 : nb);
}

char	*ft_strljoin(char *first, char *second, int len, int len2)
{
	char	*created;
	int		count;
	int		count2;

	if (len2 == -1)
		len2 = ft_strlen(second);
	if (len == -1)
	{
		len = g_len;
		g_len += len2;
	}
	if (!(created = (char*)malloc(sizeof(char) * (len + len2 + 1))))
	{
		free(first);
		return (NULL);
	}
	count = -1;
	while (++count < len)
		created[count] = first[count];
	count2 = -1;
	while (++count2 < len2)
		created[count + count2] = second[count2];
	created[count + count2] = 0;
	free(first);
	return (created);
}

int		end_conv(char *created, char *flag, int length)
{
	char	mult;

	mult = flag[9];
	while (mult--)
		g_str = ft_strljoin(g_str, created, g_len, length);
	g_len += length * flag[9];
	ft_strdel(&created);
	ft_strdel(&flag);
	return ((g_str ? 0 : -1));
}

int		end_conv_nothing(int to_return, char *flag, char *new, int size)
{
	if (!to_return)
		while (--flag[9] > 0)
			ft_memcpy(new + flag[9] * size, new, size);
	free(flag);
	return (to_return);
}
