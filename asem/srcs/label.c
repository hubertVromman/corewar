/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:41:56 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/25 13:41:57 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_label(t_file *file, char *data)
{
	int		pos_label_char;
	int		i;

	pos_label_char = ft_indexof(data, LABEL_CHAR);
	if (pos_label_char == -1)
		return (-1);
	i = -1;
	while (++i < pos_label_char)
		if (ft_indexof(LABEL_CHARS, data[i]) == -1)
			return (-1);
	if (!file->labels)
	{
		file->labels = malloc(sizeof(t_label));
		file->current_lab = file->labels;
	}
	else
	{
		file->current_lab->next = malloc(sizeof(t_label));
		file->current_lab = file->current_lab->next;
	}
	file->current_lab->pos = file->prog_size;
	file->current_lab->name = ft_strsub(data, 0, i);
	file->current_lab->next = NULL;
	file->line_off += i + 1;
	return (0);
}

int		label_length(char *str)
{
	int		c;

	c = 0;
	while (str[c] && ft_indexof(LABEL_CHARS, str[c]) != -1)
		c++;
	return (c);
}
