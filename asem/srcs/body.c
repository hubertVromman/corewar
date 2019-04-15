/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:02:14 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/12 17:02:15 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_label(t_file *file, char *data)
{
	int		pos_label_char;
	int		i;
	ft_printf("ici\n");

	pos_label_char = ft_indexof(data, LABEL_CHAR);
	if (pos_label_char == -1)
		return (-1);
	i = -1;
	while (++i < pos_label_char)
		if (ft_indexof(LABEL_CHARS, data[i]) == -1)
			return (-1);
	ft_printf("la\n");
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
	file->inline_off += i + 1;
	return (0);
}

int		get_name(t_file *file, char *data)
{
	int		i;
	int		nb_instr_max;

	if (!file->instr)
	{
		file->instr = malloc(sizeof(t_instr));
		file->current_instr = file->instr;
	}
	else
	{
		file->current_instr->next = malloc(sizeof(t_instr));
		file->current_instr = file->current_instr->next;
	}
	nb_instr_max = sizeof(g_op_tab) / sizeof(t_op) - 1;
	i = -1;
	while (++i < nb_instr_max)
		if (!strncmp(data, g_op_tab[i].name, ft_strlen(g_op_tab[i].name)))
		{
			file->current_instr->pos = i;
			file->inline_off += ft_strlen(g_op_tab[i].name);
			return (0);
		}
	return (-1);
}

// int		get_pos(t_file *file, char *data)
// {
// 	int		label_len;
// 	t_label	*iter;

// 	label_len = 0;
// 	while (ft_indexof(LABEL_CHARS, data[label_len]))
// 		label_len++;
// 	iter = file->labels;
// 	while (iter && ft_strncmp(data, iter->name, label_len))
// 		iter = iter->next;
// 	if (iter)
// 		return (iter->pos);
// 	else
// 		return (-1);
// }

int		get_params(t_file *file, char *data)
{
	int		i;
	int		sub_off;

	sub_off = 0;
	file->current_instr->nb_params = g_op_tab[file->instr.pos].param_nb;
	i = -1;
	while (++i < file->current_instr->nb_params)
	{
		//file->instr.param[i] = data + sub_off;
	}
	return (0);
}

int		get_instruction(t_file *file, char *data)
{
	t_label	*iter;

	ft_printf("%.10s\n", data + file->inline_off + file->glob_off);
	get_label(file, data + file->inline_off + file->glob_off);
	file->inline_off += skip_whitespaces(data, file->glob_off + file->inline_off);
	if (data[file->glob_off + file->inline_off] == '\n')
		end_of_line(file);// return (0);
	else
	{
		if (get_name(file, data + file->inline_off + file->glob_off) == -1)
			error_func_ln(file, 0, NULL, 0);
		file->inline_off += skip_whitespaces(data, file->glob_off + file->inline_off);
		get_params(file, data + file->glob_off + file->inline_off);
	}
	iter = file->labels;
	while (iter)
	{
		ft_printf ("%d %s\n", iter->pos, iter->name);
		iter = iter->next;
	}
	return (0);
}

int		parse_lines(t_file *file, char *data)
{
	int		count = 5;
	while (count < 10)
	{
		file->inline_off = skip_whitespaces(data, file->glob_off);
		if (data[file->glob_off + file->inline_off] == '\n')
			end_of_line(file);
		else
		{
			if (get_instruction(file, data) == -1)
				return (-1);
		}
		count++;
	}
	return (0);
}

int		create_code(t_a *all, t_file *file)
{
	if (all->flags[0])
		;
	parse_lines(file, file->s_file_content);
	return (0);
}
