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
		file->current = file->labels;
	}
	else
	{
		file->current->next = malloc(sizeof(t_label));
		file->current = file->current->next;
	}
	file->current->pos = file->prog_size;
	file->current->name = ft_strsub(data, 0, i);
	file->current->next = NULL;
	file->inline_off += i + 1;
	return (0);
}

int		get_name(t_file *file, char *data)
{
	int		i;
	int		nb_instr;

	nb_instr = sizeof(g_op_tab) / sizeof(t_op) - 1;
	i = -1;
	while (++i < nb_instr)
		if (!strncmp(data, g_op_tab[i].name, ft_strlen(g_op_tab[i].name)))
		{
			file->instr.pos = i;
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
	int		nb_params;
	int		sub_off;

	sub_off = 0;
	nb_params = g_op_tab[file->instr.pos].param_nb;
	i = -1;
	while (++i < nb_params)
	{
		if (data[sub_off] == DIRECT_CHAR && ++sub_off)
		{
			if (data[sub_off] == LABEL_CHAR && ++sub_off)
				;// file->instr.param[i] = get_pos(t_file *file, data + sub_off);
			else
				file->instr.param[i] = ft_atoi(data + sub_off);
			ft_printf("%d\n", file->instr.param[i]);
			sub_off += 2;
		}
		else
			return (0);
	}
	return (0);
}

int		get_instruction(t_file *file, char *data)
{
	// char	*buffer;
	// int		values[MAX_ARGS_NUMBER];
	t_label *iter;

	get_label(file, data + file->inline_off + file->glob_off);
	file->inline_off += skip_whitespaces(data, file->glob_off + file->inline_off);
	if (get_name(file, data + file->inline_off + file->glob_off) == -1)
		error_func_ln(file, 0, NULL, 0);
	file->inline_off += skip_whitespaces(data, file->glob_off + file->inline_off);
	get_params(file, data + file->glob_off + file->inline_off);
	ft_printf("%d\n", file->instr.param[0]);
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
	while (1)
	{
		file->inline_off = skip_whitespaces(data, file->glob_off);
		if (data[file->glob_off + file->inline_off] == '\n')
			end_of_line(file);
		else
		{
			if (get_instruction(file, data) == -1)
				return (-1);
			return (0);
		}
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
