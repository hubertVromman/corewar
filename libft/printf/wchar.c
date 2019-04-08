/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:49:12 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 14:49:13 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*wchar_to_char2(wchar_t c, int *size, unsigned char *s)
{
	char	*created;

	if (c < 65536)
	{
		*size = 3;
		if (!(created = (char*)malloc(sizeof(char) * 3)))
			return (NULL);
		created[0] = 224 + s[1] / 16;
		created[1] = 128 + s[1] % 16 * 4 + s[0] / 64;
		created[2] = 128 + s[0] % 64;
	}
	else
	{
		*size = 4;
		if (!(created = (char*)malloc(sizeof(char) * 4)))
			return (NULL);
		created[0] = 240 + s[2] / 4 % 8;
		created[1] = 128 + s[2] % 4 * 16 + s[1] / 16;
		created[2] = 128 + s[1] % 16 * 4 + s[0] / 64;
		created[3] = 128 + s[0] % 64;
	}
	return (created);
}

char	*wchar_to_char(wchar_t c, int *size)
{
	char			*created;
	unsigned char	*s;

	s = (unsigned char *)&c;
	if (c < 128)
	{
		*size = 1;
		if (!(created = (char*)malloc(sizeof(char) * 1)))
			return (NULL);
		created[0] = s[0];
	}
	else if (c < 2048)
	{
		*size = 2;
		if (!(created = (char*)malloc(sizeof(char) * 2)))
			return (NULL);
		created[0] = 192 + s[1] % 32 * 4 + s[0] / 64;
		created[1] = 128 + s[0] % 64;
	}
	else
		return (wchar_to_char2(c, size, s));
	return (created);
}

int		lchar_func(wint_t c, char *flag, int width[2])
{
	char	*created;
	char	*tmp;
	int		size;

	if (!(created = wchar_to_char(c, &size)))
		return (end_conv_nothing(-1, flag, NULL, 0));
	if (width[0] > size)
	{
		tmp = created;
		created = ft_strnew(width[0]);
		ft_memcpy(created + (flag[3] ? 0 : width[0] - size), tmp, size);
		free(tmp);
		if (flag[3])
			ft_memset(created + size, ' ', width[0] - size);
		else
			ft_memset(created, flag[2] ? '0' : ' ', width[0] - size);
		size = width[0];
	}
	return (end_conv(created, flag, size));
}

char	*wchar_to_char_arr(wchar_t *s, int *tot, int prec)
{
	int		count;
	char	*created;
	char	*tmp2;
	int		size;

	if (!(created = ft_strnew(0)))
		return (NULL);
	count = -1;
	while (s[++count])
	{
		tmp2 = wchar_to_char(s[count], &size);
		if (prec != -1 && *tot + size > prec)
		{
			free(tmp2);
			return (created);
		}
		created = ft_strljoin(created, tmp2, ft_strlen(created), size);
		*tot += size;
		free(tmp2);
	}
	return (created);
}

int		lstring_func(wchar_t *s, char *flag, int width[2])
{
	char	*created;
	char	*tmp;
	int		size;
	int		len;

	if (!s)
		s = L"(null)";
	len = 0;
	if (!(created = wchar_to_char_arr(s, &len, width[1])))
		return (end_conv_nothing(-1, flag, NULL, 0));
	size = ft_max(width[0], len);
	tmp = created;
	if (!(created = realloc_g_str(size * flag[9])))
		return (end_conv_nothing(-1, flag, NULL, 0));
	ft_memcpy(created + (flag[3] ? 0 : size - len), tmp, len);
	free(tmp);
	if (flag[3])
		ft_memset(created + len, ' ', size - len);
	else
		ft_memset(created, flag[2] ? '0' : ' ', size - len);
	return (end_conv_nothing(0, flag, created, size));
}
