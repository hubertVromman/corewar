/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:05:09 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/25 16:05:11 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		encode_type(t_file *file, char *data, t_param *param, int *extend_size)
{
	int		data_size;

	data_size = 0;
	if (data[0] == 'r')
	{
		param->size = 1;
		param->kind = T_REG;
		param->base = 10;
		data_size = 1 + nb_digits(data + 1, NULL);
	}
	else
	{
		if ((data_size = data[0] == DIRECT_CHAR) &&
			(param->kind = T_DIR))
			param->size = 4 - 2 *
				g_op_tab[file->curr_instr->index].dir_size;
		else if ((param->kind = T_IND))
			param->size = 2;
		data_size += data[data_size] == LABEL_CHAR ? 1 +
label_length(data + 1 + data_size) : nb_digits(data + data_size, &param->base);
		if (g_all.flags[OPERATION] || file->extend)
			*extend_size = get_operations(file, data + data_size,
				data_size, param);
	}
	return (data_size);
}

int		get_error(t_file *file, char *data, t_var *var, char *param)
{
	if (!strcmp(param, "%") || !ft_strcmp(param, "r"))
		wrong_char(file, "number", var->sub_off);
	else if (!ft_strcmp(param, "%:") || !ft_strcmp(param, ":"))
		wrong_char(file, "label_char", var->sub_off);
	else if (!var->data_size)
		wrong_char(file, "param", var->sub_off);
	else if (var->i == file->curr_instr->nb_params)
	{
		if (data[var->sub_off] != '\n')
			wrong_char(file, "\\n", var->sub_off);
	}
	else if (data[var->sub_off] != SEPARATOR_CHAR)
		wrong_char(file, ",", var->sub_off);
	else
		return (0);
	return (-1);
}

int		get_params(t_file *file, char *data)
{
	t_var	var;

	ft_bzero(&var, sizeof(var));
	while (1)
	{
		var.extend_size = 0;
		var.sub_off += skip_spaces(data, var.sub_off);
		var.data_size = encode_type(file, data + var.sub_off,
			&file->curr_instr->params[var.i], &var.extend_size);
		if (!(g_op_tab[file->curr_instr->index].param[var.i]
			& file->curr_instr->params[var.i].kind))
		{
			error_func_ln(file, WRONG_TYPE, NULL, 0);
			return (var.sub_off);
		}
		file->curr_instr->params[var.i].line_off = file->line_off + var.sub_off;
		if (!(file->curr_instr->params[var.i].data =
			ft_strsub(data, var.sub_off, var.data_size)))
			exit_func(-2, 0);
		var.sub_off += skip_spaces(data,
			var.sub_off += var.data_size + var.extend_size);
		if (get_error(file, data, &var,
			file->curr_instr->params[var.i++].data))
			return (var.sub_off);
		var.sub_off++;
	}
}

int		parse_name(t_file *file, char *data, int i)
{
	int		ret;
	int		sub_off;

	file->curr_instr->index = i;
	file->curr_instr->line_nb = file->line_nb;
	file->curr_instr->nb_params = g_op_tab[i].nb_params;
	sub_off = ft_strlen(g_op_tab[i].name);
	file->line_off += sub_off;
	ret = get_params(file, data + sub_off);
	while (data[sub_off + ret] && data[sub_off + ret] != '\n')
		ret++;
	file->line_off += ret;
	if (data[sub_off + ret] == '\n')
		end_of_line(file);
	return (0);
}

int		get_name(t_file *file, char *data)
{
	int		i;
	int		instr_length;

	if ((i = -1) && !file->instr)
	{
		if (!(file->instr = ft_memalloc(sizeof(t_instr))))
			exit_func(-2, 0);
		file->curr_instr = file->instr;
	}
	else
	{
		if (!(file->curr_instr->next = ft_memalloc(sizeof(t_instr))))
			exit_func(-2, 0);
		file->curr_instr = file->curr_instr->next;
	}
	while (ft_isalpha(data[++i]))
		;
	if (!(instr_length = i))
		return (wrong_char(file, "instruction", 0));
	i = -1;
	while (++i < (int)(sizeof(g_op_tab) / sizeof(t_op) - 1))
		if (!strncmp(data, g_op_tab[i].name, instr_length))
			return (parse_name(file, data, i));
	return (error_func_ln(file, INSTR_NOT_FOUND,
		ft_strsub(data, 0, instr_length), 1));
}
