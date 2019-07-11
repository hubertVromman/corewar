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

char	*get_cor_name(char *file)
{
	int		len;
	char	*new_name;

	len = ft_strlen(file);
	if (!(new_name = malloc(len + 3)))
		exit_func(-2, 0);
	ft_memcpy(new_name, file, len - 1);
	ft_memcpy(new_name + len - 1, "cor", 3);
	new_name[len + 2] = 0;
	return (new_name);
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
