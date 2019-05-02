/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:25:15 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/25 15:25:17 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	get_codage(t_instr *current)
{
	char	codage;
	int		i;

	codage = 0;
	i = -1;
	while (++i < current->nb_params)
	{
		if (current->params[i].kind & (T_IND | T_DIR))
			codage |= 1 << (7 - 2 * i);
		if (current->params[i].kind & (T_IND | T_REG))
			codage |= 1 << (6 - 2 * i);
	}
	return (codage);
}

int		write_instr(t_file *file)
{
	int		offset;
	t_instr	*current;

	offset = 0;
	current = file->instr;
	while (current)
	{
		offset = current->pos_in_file;
		file->prog_content[offset++] = g_op_tab[current->index].opcode;
		if (g_op_tab[current->index].codage)
			file->prog_content[offset++] = get_codage(current);
		current = current->next;
	}
	return (0);
}

int		get_label_pos(t_file *file, char *label)
{
	t_label	*current;

	current = file->labels;
	while (current)
	{
		if (!ft_strcmp(label, current->name))
			return (current->pos);
		current = current->next;
	}
	return (-1);
}

int		get_encoded_param(t_file *file, t_param *param,
	int pos_in_file, int *ret)
{
	int		nb;
	int		off;

	*ret = 0;
	if (param->kind & T_REG)
		*ret = get_normal_base(param->data + 1, param->base);
	else
	{
		off = !!(param->kind & T_DIR);
		if (param->data[off] == LABEL_CHAR)
		{
			if ((nb = get_label_pos(file, param->data + 1 + off)) == -1)
			{
				file->line_off = param->line_off;
				file->line_nb = file->curr_instr->line_nb + 1;
				return (-1);
			}
			*ret = nb - pos_in_file;
		}
		else
			*ret = get_normal_base(param->data + off, param->base);
	}
	*ret += get_extend(file, param, pos_in_file);
	*ret = little_to_big_endian(*ret);
	return (0);
}

int		write_params(t_file *file)
{
	int		offset;
	int		i;
	t_instr	*current;
	int		ret;

	offset = 0;
	current = file->instr;
	while (current)
	{
		offset += 1 + g_op_tab[current->index].codage;
		i = -1;
		while (++i < current->nb_params)
		{
			file->curr_instr = current;
			if ((get_encoded_param(file, &current->params[i],
				current->pos_in_file, &ret)) == -1)
				error_func_ln(file, NOT_LABEL, current->params[i].data, 0);
			ret >>= (8 * (4 - current->params[i].size));
			ft_memcpy(file->prog_content + offset, &ret,
				current->params[i].size);
			offset += current->params[i].size;
		}
		current = current->next;
	}
	return (0);
}
