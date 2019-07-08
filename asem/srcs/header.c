/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:00:26 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/12 17:00:27 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_command_data(t_file *file, char *data, char **to_fill)
{
	int		start_search;

	file->line_off++;
	start_search = file->glob_off + file->line_off;
	while (data[file->glob_off + file->line_off])
	{
		if (data[file->glob_off + file->line_off] == '\n')
			end_of_line(file);
		else if (data[file->glob_off + file->line_off] == '"')
		{
			if (!*to_fill)
				if (!(*to_fill = ft_strsub(data, start_search,
					file->glob_off + file->line_off - start_search)))
					exit_func(-2, 0);
			file->line_off++;
			break ;
		}
		else
			file->line_off++;
	}
	return (0);
}

int		check_command(t_file *file, char *data, char **to_fill, char *cmd_name)
{
	if (*to_fill)
		error_func_ln(file, TWO_CMD, cmd_name + 1, 0);
	file->line_off += ft_strlen(cmd_name);
	file->line_off += skip_spaces(data,
		file->glob_off + file->line_off);
	if (data[file->glob_off + file->line_off] == '"')
	{
		get_command_data(file, data, to_fill);
		file->line_off += skip_spaces(data,
			file->glob_off + file->line_off);
		if (data[file->glob_off + file->line_off] != '\n')
			wrong_char(file, "\\n", 0);
	}
	else
		wrong_char(file, "\"", 0);
	while (data[file->glob_off + file->line_off] != '\n' &&
		data[file->glob_off + file->line_off])
		file->line_off++;
	if (data[file->glob_off + file->line_off])
		end_of_line(file);
	else
		return (error_func_ln(file, UNEXP_EOF, NULL, 0));
	return (0);
}

int		get_command_name(t_file *file, char *data)
{
	if (!ft_strncmp(data + file->glob_off + file->line_off,
		NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		if (check_command(file, data, &file->prog_name, NAME_CMD_STRING) == -1)
			return (-1);
	}
	else if (!ft_strncmp(data + file->glob_off + file->line_off,
		COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
	{
		if (check_command(file, data, &file->prog_comment, COMMENT_CMD_STRING)
			== -1)
			return (-1);
	}
	else if (!ft_strncmp(data + file->glob_off + file->line_off, ".extend", 7))
	{
		file->line_off += skip_spaces(data, file->glob_off +
			(file->line_off += 7));
		if (data[file->glob_off + file->line_off] == '\n')
			end_of_line(file);
		file->extend = 1;
	}
	else
		return (error_command(file, data));
	return (0);
}

int		get_cmds(t_file *file, char *data)
{
	while (1)
	{
		file->line_off = skip_spaces(data, file->glob_off);
		if (data[file->glob_off + file->line_off] == '\n')
			end_of_line(file);
		else if (!data[file->glob_off + file->line_off])
			return (wrong_char(file, "instruction", 0));
		else if (data[file->glob_off + file->line_off] == '.')
		{
			if (get_command_name(file, data) == -1)
				return (-1);
		}
		else
			break ;
	}
	return (0);
}

int		create_header(t_a *all, t_file *file)
{
	int		magic;
	int		offset;

	magic = change_endianness(COREWAR_EXEC_MAGIC);
	if (!(file->header = ft_memalloc(all->header_size)))
		exit_func(-2, 0);
	ft_memcpy(file->header, &magic, offset = 4);
	if (get_cmds(file, file->s_file_content) == -1)
		return (-1);
	if (!file->prog_name)
		error_func(file, NAME_NOT_FOUND);
	else if (ft_strlen(file->prog_name) > PROG_NAME_LENGTH)
		error_func(file, NAME_TOO_LONG);
	else if (!file->prog_comment)
		error_func(file, COMMENT_NOT_FOUND);
	else if (ft_strlen(file->prog_comment) > COMMENT_LENGTH)
		error_func(file, COMMENT_TOO_LONG);
	if (!file->nb_error)
		ft_memcpy(file->header + offset,
			file->prog_name, ft_strlen(file->prog_name));
	offset += PROG_NAME_LENGTH + 4 + 4;
	if (!file->nb_error)
		ft_memcpy(file->header + offset,
			file->prog_comment, ft_strlen(file->prog_comment));
	return (0);
}
