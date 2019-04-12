/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:44:43 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/12 16:44:45 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		error_func(t_file *file, int error_code)
{
	ft_printf("<b bwhite>%s: <bred>error:<b bwhite> %>", file->s_name, 2);
	if (error_code == NOT_S_FILE)
		ft_printf("not a .s file\n%>", 2);
	else if (error_code == OPEN_FAIL)
		ft_printf("open failed\n%>", 2);
	else if (error_code == NOT_CREATE)
		ft_printf("could not open or create %s\n%>", file->cor_name, 2);
	else if (error_code == NAME_TOO_LONG)
		ft_printf("program name too long (max size : %d)\n%>", PROG_NAME_LENGTH, 2);
	else if (error_code == NAME_NOT_FOUND)
		ft_printf("program name not found\n%>", 2);
	else if (error_code == COMMENT_TOO_LONG)
		ft_printf("program comment too long (max size : %d)\n%>", COMMENT_LENGTH, 2);
	else if (error_code == COMMENT_NOT_FOUND)
		ft_printf("program comment not found\n%>", 2);
	else
		ft_printf("undifined error\n%>", 2);
	ft_printf("</>%>", 2);
	file->nb_error++;
	return (-1);
}

int		error_func_ln(t_file *file, int error_code, char *detail, int to_free)
{
	ft_printf("<b bwhite>%s:%d:%d: <bred>error:<bwhite> %>", file->s_name, file->line_nb, file->inline_off, 2);
	if (error_code == CMD_NOT_FOUND)
		ft_printf("command '%s' not found\n%>", detail, 2);
	else if (error_code == UNEXP_EOF)
		ft_printf("unexpected EOF\n%>", 2);
	else if (error_code == TWO_CMD)
		ft_printf("command '%s' already found\n%>", detail, 2);
	else
		ft_printf("undifined error\n%>", 2);
	ft_printf("</>%>", 2);
	if (to_free)
		free(detail);
	file->nb_error++;
	return (-1);
}

int		wrong_char(t_file *file, char *expected)
{
	ft_printf("<b bwhite>%s:%d:%d: <bred>error:<bwhite> %>", file->s_name, file->line_nb + 1, file->inline_off + 1, 2);
	ft_printf("wrong char, expected '%s', got '%c' (%p)\n%></>", expected, file->s_file_content[file->glob_off + file->inline_off], file->s_file_content[file->glob_off + file->inline_off], 2);
	file->nb_error++;
	return (-1);
}

int		error_command(t_file *file, char *data)
{
	int		end_command;

	file->inline_off++;
	end_command = 0;
	while (data[file->glob_off + file->inline_off + end_command] != ' ' &&
data[file->glob_off + file->inline_off + end_command] != '\t' &&
data[file->glob_off + file->inline_off + end_command] != '\n' &&
data[file->glob_off + file->inline_off + end_command])
		end_command++;
	error_func_ln(file, CMD_NOT_FOUND, ft_strsub(data, file->glob_off + file->inline_off, end_command), 1);
	file->inline_off += end_command;
	while (data[file->glob_off + file->inline_off] != '\n' && data[file->glob_off + file->inline_off])
		file->inline_off++;
	if (!data[file->glob_off + file->inline_off])
		error_func_ln(file, UNEXP_EOF, NULL, 0);
	end_of_line(file);
	return (0);
}