/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 10:29:15 by hvromman          #+#    #+#             */
/*   Updated: 2019/05/02 10:29:17 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_operations(t_file *file, char *data, int offset, t_param *param)
{
	int		size;
	t_param	*new;
	int		sub_off;

	sub_off = skip_spaces(data, 0);
	if (data[sub_off] == '+' || data[sub_off] == '-')
	{
		new = ft_memalloc(sizeof(t_param));
		param->extend_op = new;
		new->kind = data[sub_off++] == '+';
		sub_off += skip_spaces(data, sub_off);
		if ((size = data[sub_off] == ':'))
		{
			while (ft_indexof(LABEL_CHARS, data[sub_off + size]) != -1)
				size++;
		}
		else
			size = nb_digits(data + sub_off, &new->base);
		new->line_off += offset + sub_off;
		if (!(new->data = ft_strsub(data, sub_off, size)))
			exit_func(-2, 0);
		return (get_operations(file, data + sub_off + size, offset, new)
			+ sub_off + size);
	}
	return (0);
}

int		get_extend(t_file *file, t_param *param, int pos_in_file)
{
	int		ret;
	int		nb;

	param = param->extend_op;
	ret = 0;
	while (param)
	{
		if (param->data[0] == LABEL_CHAR)
		{
			if ((nb = get_label_pos(file, param->data + 1)) == -1)
			{
				file->line_off = param->line_off;
				file->line_nb = file->curr_instr->line_nb + 1;
				error_func_ln(file, NOT_LABEL, param->data, 0);
			}
			nb -= pos_in_file;
		}
		else
			nb = get_normal_base(param->data, param->base);
		ret += (param->kind ? 1 : -1) * nb;
		param = param->extend_op;
	}
	return (ret);
}
