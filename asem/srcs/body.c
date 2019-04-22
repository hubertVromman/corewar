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

int		nb_digits(char *str)
{
	int		c;

	c = *str == '-';
	while (ft_isdigit(str[c]))
		c++;
	return (c);
}

int		label_length(char *str)
{
	int		c;

	c = 0;
	while (str[c] && ft_indexof(LABEL_CHARS, str[c]) != -1)
		c++;
	return (c);
}

int		get_params(t_file *file, char *data)
{
	int		i;
	int		sub_off;
	int		data_size;

	sub_off = 0;
	i = 0;
	while (1)
	{
		data_size = 0;
		sub_off += skip_whitespaces(data, sub_off);
		if (data[sub_off] == 'r')
		{
			file->current_instr->params[i].size = 1;
			file->current_instr->params[i].kind = T_REG;
			data_size = 1 + nb_digits(data + sub_off + 1);
		}
		else
		{ 
			if ((data_size = data[sub_off] == DIRECT_CHAR) && (file->current_instr->params[i].kind = T_DIR))
				file->current_instr->params[i].size = 4 - 2 * g_op_tab[file->current_instr->index].dir_size;
			else if ((file->current_instr->params[i].kind = T_IND))
				file->current_instr->params[i].size = 2;
			if (data[sub_off + data_size] == LABEL_CHAR)
				data_size += 1 + label_length(data + sub_off + 1 + data_size);
			else
				data_size += nb_digits(data + sub_off + data_size);
		}
		file->current_instr->params[i].inline_off = file->inline_off + sub_off;
		file->current_instr->params[i].data = ft_strsub(data, sub_off, data_size);
		i++;
		sub_off += data_size;
		sub_off += skip_whitespaces(data, sub_off);
		if (!data_size)
		{
			wrong_char(file, "param", sub_off);
			return (sub_off);
		}
		else if (i == file->current_instr->nb_params)
		{
			if (data[sub_off] != '\n')
				wrong_char(file, "\\n", sub_off);
			return (sub_off);
		}
		else if (data[sub_off] != ',')
		{
			wrong_char(file, ",", sub_off);
			return (sub_off);
		}
		sub_off++;
	}
}

int		get_name(t_file *file, char *data)
{
	int		i;
	int		max_index;
	int		sub_off;
	int		ret;
	int		instr_length;

	if (!file->instr)
	{
		file->instr = ft_memalloc(sizeof(t_instr));
		file->current_instr = file->instr;
	}
	else
	{
		file->current_instr->next = ft_memalloc(sizeof(t_instr));
		file->current_instr = file->current_instr->next;
	}
	max_index = sizeof(g_op_tab) / sizeof(t_op) - 1;
	i = -1;
	while (ft_isalpha(data[++i]))
		;
	instr_length = i;
	ft_printf("instr_length %d", instr_length);
	i = -1;
	while (++i < max_index)
		if (!strncmp(data, g_op_tab[i].name, instr_length))
		{
			file->current_instr->index = i;
			file->current_instr->line_nb = file->line_nb;
			file->current_instr->nb_params = g_op_tab[i].param_nb;
			sub_off = ft_strlen(g_op_tab[i].name);
			file->inline_off += sub_off;
			ft_printf("start param <%.10s>\n", data + sub_off);
			ret = get_params(file, data + sub_off);
			while (data[sub_off + ret] && data[sub_off + ret] != '\n')
				ret++;
			file->inline_off += ret;
			if (data[sub_off + ret] == '\n')
			end_of_line(file);
			for (int i = 0; i < file->current_instr->nb_params; i++)
				ft_printf("-- %d <%s>\n", i, file->current_instr->params[i].data);
			return (0);
		}
	return (-1);
}

int		get_instruction(t_file *file, char *data)
{
	int		i;

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
		file->current_instr->size = 1 + g_op_tab[file->current_instr->index].codage;
		i = -1;
		while (++i < file->current_instr->nb_params)
			file->current_instr->size += file->current_instr->params[i].size;
		file->current_instr->pos_in_file = file->prog_size;
		file->prog_size += file->current_instr->size;
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
		else if (!data[file->glob_off + file->inline_off])
			return (0);
		else
		{
			if (get_instruction(file, data) == -1)
				return (-1);
			if (!data[file->glob_off + file->inline_off])
				return (0);
		}
	}
	return (0);
}

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

int		get_encoded_param(t_file *file, t_param *param, int pos_in_file)
{
	int		nb;

	nb = 0;
	// ft_printf ("%d <%s>\n", param->kind, param->data);
	if (param->kind & T_REG)
		nb = atoi(param->data + 1);
	else if (param->kind & T_DIR)
	{
		if (param->data[1] == ':')
			nb = get_label_pos(file, param->data + 2) - pos_in_file;
		else
			nb = atoi(param->data + 1);
	}
	else
	{
		ft_printf ("<%s>\n", param->data);
		if (param->data[0] == ':')
			nb = get_label_pos(file, param->data + 1) - pos_in_file;
		else
			nb = atoi(param->data);
		ft_printf("%d\n", nb);
	}
	return (little_to_big_endian(nb));
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
		offset++;
		if (g_op_tab[current->index].codage)
			offset++;
		i = -1;
		while (++i < current->nb_params)
		{
			ret = get_encoded_param(file, &current->params[i], current->pos_in_file);
			ret = ret >> (8 * (4 - current->params[i].size));
			ft_memcpy(file->prog_content + offset, &ret, current->params[i].size);
			offset += current->params[i].size;
		}
		current = current->next;
	}
	return (0);
}

int		create_code(t_a *all, t_file *file)
{
	int		size;

	if (all->flags[0])
		;
	parse_lines(file, file->s_file_content);
	// file->current_instr = file->instr;
	// while (file->current_instr)
	// {
	// 	ft_printf ("%s : %d param(s)\n", g_op_tab[file->current_instr->index].name, file->current_instr->nb_params);
	// 	for (int i = 0; i < file->current_instr->nb_params; i++)
	// 		ft_printf("	%s\n", file->current_instr->params[i].data);
	// 	file->current_instr = file->current_instr->next;
	// }
	file->prog_content = ft_memalloc(file->prog_size);
	write_instr(file);
	encode_labels(file);


	// t_label *iter;

	// iter = file->labels;
	// while (iter)
	// {
	// 	ft_printf ("-> %d %s\n", iter->pos, iter->name);
	// 	iter = iter->next;
	// }

	write_params(file);
	size = little_to_big_endian(file->prog_size);
	ft_memcpy(file->header + 8 + PROG_NAME_LENGTH, &size, 4);
	return (0);
}
