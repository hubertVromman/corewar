/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:54:12 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/12 16:54:14 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_ext(char *str)
{
	return (str + ft_last_indexof(str, '.') + 1);
}

char	*get_cor_name(char *file)
{
	int		len;
	char	*new_name;

	len = ft_strlen(file);
	new_name = malloc(len + 3);
	ft_memcpy(new_name, file, len - 1);
	ft_memcpy(new_name + len - 1, "cor", 3);
	new_name[len + 2] = 0;
	return (new_name);
}

int		little_to_big_endian(int little)
{
	int		big;

	big = ((little >> 24) & 0xff) |
		((little >> 8) & 0xff00) |
		((little << 8) & 0xff0000) |
		((little << 24) & 0xff000000);
	return (big);
}

int		skip_spaces(char *data, int offset)
{
	int		sub_off;

	sub_off = 0;
	while (data[offset + sub_off] == ' ' || data[offset + sub_off] == '\t')
		sub_off++;
	if (data[offset + sub_off] == COMMENT_CHAR)
	{
		while (data[offset + sub_off] != '\n' && data[offset + sub_off])
			sub_off++;
	}
	return (sub_off);
}

int		end_of_line(t_file *file)
{
	file->glob_off += file->line_off + 1;
	file->line_nb++;
	file->line_off = 0;
	return (0);
}
