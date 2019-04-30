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
	int		i;

	if (ft_indexof(data, LABEL_CHAR) == (i = -1))
		return (-1);
	while (++i < ft_indexof(data, LABEL_CHAR))
		if (ft_indexof(LABEL_CHARS, data[i]) == -1)
			return (-1);
	if (!file->labels)
	{
		if (!(file->labels = malloc(sizeof(t_label))))
			exit_func(-2, 0);
		file->current_lab = file->labels;
	}
	else
	{
		if (!(file->current_lab->next = malloc(sizeof(t_label))))
			exit_func(-2, 0);
		file->current_lab = file->current_lab->next;
	}
	file->current_lab->pos = file->prog_size;
	if (!(file->current_lab->name = ft_strsub(data, 0, i)))
		exit_func(-2, 0);
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
