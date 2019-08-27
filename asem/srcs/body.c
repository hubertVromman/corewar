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

int		get_instruction(t_file *file, char *data)
{
	int		i;

	get_label(file, data + file->line_off + file->glob_off);
	file->line_off += skip_spaces(data, file->glob_off + file->line_off);
	if (data[file->glob_off + file->line_off] == '\n' ||
		!data[file->glob_off + file->line_off])
		return (end_of_line(file));
	else if ((i = -1))
	{
		if (get_name(file, data + file->line_off + file->glob_off) == -1)
		{
			while (data[file->line_off + file->glob_off] != '\n' &&
				data[file->line_off + file->glob_off])
				file->line_off++;
			return (end_of_line(file));
		}
		file->line_off += skip_spaces(data, file->glob_off + file->line_off);
		file->curr_instr->size = 1 +
			g_op_tab[file->curr_instr->index].codage;
		while (++i < file->curr_instr->nb_params)
			file->curr_instr->size += file->curr_instr->params[i].size;
		file->curr_instr->pos_in_file = file->prog_size;
		file->prog_size += file->curr_instr->size;
	}
	return (0);
}

int		parse_lines(t_file *file, char *data)
{
	while (1)
	{
		file->line_off = skip_spaces(data, file->glob_off);
		if (data[file->glob_off + file->line_off] == '\n')
			end_of_line(file);
		else if (!data[file->glob_off + file->line_off])
			return (0);
		else
		{
			if (get_instruction(file, data) == -1)
				return (-1);
			if (!data[file->glob_off + file->line_off])
				return (0);
		}
	}
	return (0);
}

int		encode_labels(t_file *file)
{
	t_label	*current;

	current = file->labels;
	while (current)
	{
		current->content = file->prog_content[current->pos];
		current = current->next;
	}
	return (0);
}

int		create_code(t_a *all, t_file *file)
{
	int		size;

	(void)all;
	parse_lines(file, file->s_file_content);
	if (!(file->prog_content = ft_memalloc(file->prog_size)))
		exit_func(-2, 0);
	write_instr(file);
	encode_labels(file);
	if (file->nb_error)
		return (0);
	write_params(file);
	size = change_endianness(file->prog_size);
	ft_memcpy(file->header + 8 + PROG_NAME_LENGTH, &size, 4);
	return (0);
}
