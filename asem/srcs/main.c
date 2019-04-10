/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:30:00 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/06 14:30:04 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		free_all(t_a *all)
{
	free(all->flags);
	return (0);
}

char	*get_ext(char *str)
{
	return (str + ft_last_indexof(str, '.') + 1);
}

int		usage(void)
{
	ft_printf("usage: asm: [-%s] file.s ...\n%>", OP, 2);
	ft_printf("      -m  : Unable to compile multiple files\n%>", 2);
	return (0);
}

int		exit_func(int exit_code, int dp_usage, t_a *all)
{
	if (dp_usage)
		usage();
	free_all(all);
	exit(exit_code);
}

// int		print_general_error(t_file *file)
// {
// 	ft_printf("%s: <b bred>error:</> %>", file->s_name, 2);
// 	return (0);
// }

int		error_func(t_file *file, int error_code)
{
	ft_printf("<b bwhite>%s: <bred>error:<b bwhite> %>", file->s_name, 2);
	if (error_code == NOT_S_FILE)
		ft_printf("not a .s file\n%>", 2);
	else if (error_code == OPEN_FAIL)
		ft_printf("open failed\n%>", 2);
	else if (error_code == NOT_CREATE)
		ft_printf("could not create %s\n%>", file->cor_name, 2);
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

int		wrong_char(t_file *file, char *expected)
{
	ft_printf("<b bwhite>%s:%d:%d: <bred>error:<bwhite> %>", file->s_name, file->line_nb, file->inline_off, 2);
	ft_printf("wrong char, expected '%s', got '%c' (%#x)\n%></>", expected, file->s_file_content[file->glob_off + file->inline_off], file->s_file_content[file->glob_off + file->inline_off], 2);
	file->nb_error++;
	return (-1);
}

int		error_func_ln(t_file *file, int error_code, char *error_detail)
{
	ft_printf("<b bwhite>%s:%d:%d: <bred>error:</> %>", file->s_name, file->line_nb, file->inline_off, 2);
	if (error_code == CMD_NOT_FOUND)
		ft_printf("command '%s' not found\n%>", error_detail, 2);
	else if (error_code == UNEXP_EOF)
		ft_printf("unexpected EOF\n%>", 2);
	else
		ft_printf("undifined error\n%>", 2);
	free(error_detail);
	ft_printf("</>%>", 2);
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
	error_func_ln(file, CMD_NOT_FOUND, ft_strsub(data, file->glob_off + file->inline_off, end_command));
	return (-1);
}

int		get_flags(int ac, char **av, t_a *all)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "--"))
			return (i + 1);
		if (av[i][0] == '-')
		{
			j = 0;
			while (av[i][++j])
			{
				if ((k = ft_indexof(OP, av[i][j])) == -1)
					exit_func(-1, 1, all);
				all->flags[k] = 1;
			}
		}
		else
			return (i);
	}
	return (i);
}

char	*get_cor_name(char *file)
{
	int		len;
	char	*new_name;

	len = ft_strlen(file);
	new_name = malloc(len + 3);
	ft_memcpy(new_name, file, len - 1);
	ft_memcpy(new_name + len - 1, "cor", 3);
	new_name[len + 2] = 0;
	return (new_name);
}

int		little_to_big_endian(int little)
{
	int		big;

	big = ((little >> 24) & 0xff) |
		((little >> 8) & 0xff00) |
		((little << 8) & 0xff0000) |
		((little << 24) & 0xff000000);
	return (big);
}

int		skip_whitespaces(char *data, int offset)
{
	int		sub_off;

	sub_off = 0;
	while (data[offset + sub_off] == ' ' || data[offset + sub_off] == '\t')
		sub_off++;
	return (sub_off);
}

int		get_name(t_file *file, char *data)
{
	int		start_search;

	file->inline_off++;
	start_search = file->glob_off + file->inline_off;
	while (data[file->glob_off + file->inline_off])
	{
		if (data[file->glob_off + file->inline_off] == '\n')
		{
			file->line_nb++;
			file->glob_off += file->inline_off + 1;
			file->inline_off = 0;
		}
		else if (data[file->glob_off + file->inline_off] == '"')
		{
			file->prog_name = ft_strsub(data, start_search, file->glob_off + file->inline_off++ - start_search);
			break;
		}
		else
			file->inline_off++;
	}
	return (0);
}

int		get_comment(t_file *file, char *data)
{
	int		start_search;

	file->inline_off++;
	start_search = file->glob_off + file->inline_off;
	while (data[file->glob_off + file->inline_off])
	{
		if (data[file->glob_off + file->inline_off] == '\n')
		{
			file->line_nb++;
			file->glob_off += file->inline_off + 1;
			file->inline_off = 0;
		}
		else if (data[file->glob_off + file->inline_off] == '"')
		{
			file->prog_comment = ft_strsub(data, start_search, file->glob_off + file->inline_off++ - start_search);
			break;
		}
		else
			file->inline_off++;
	}
	return (0);
}

int		check_command(t_file *file, char *data)
{
	if (!ft_strncmp(data + file->glob_off + file->inline_off, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		file->inline_off += ft_strlen(NAME_CMD_STRING) + 1;
		file->inline_off += skip_whitespaces(data, file->glob_off + file->inline_off);
		if (data[file->glob_off + file->inline_off] == '"')
		{
			get_name(file, data);
			file->inline_off += skip_whitespaces(data, file->glob_off + file->inline_off);
			if (data[file->glob_off + file->inline_off] != '\n')
				wrong_char(file, "\\n");
		}
		else
			wrong_char(file, "\"");
		while (data[file->glob_off + file->inline_off] != '\n' && data[file->glob_off + file->inline_off])
			file->inline_off++;
		if (data[file->glob_off + file->inline_off])
		{
			file->glob_off += file->inline_off + 1;
			file->inline_off = 0;
			file->line_nb++;
		}
		else
			error_func_ln(file, UNEXP_EOF, NULL);
		ft_printf("%s %d %d %d\n", file->prog_name, file->glob_off, file->inline_off, file->line_nb);
	}
	else if (!ft_strncmp(data + file->glob_off + file->inline_off, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
	{
		file->inline_off += ft_strlen(COMMENT_CMD_STRING) + 1;
		file->inline_off += skip_whitespaces(data, file->glob_off + file->inline_off);
		if (data[file->glob_off + file->inline_off] == '"')
		{
			get_comment(file, data);
			file->inline_off += skip_whitespaces(data, file->glob_off + file->inline_off);
			if (data[file->glob_off + file->inline_off] != '\n')
				wrong_char(file, "\\n");
		}
		else
			wrong_char(file, "\"");
		while (data[file->glob_off + file->inline_off] != '\n' && data[file->glob_off + file->inline_off])
			file->inline_off++;
		if (data[file->glob_off + file->inline_off])
		{
			file->glob_off += file->inline_off + 1;
			file->inline_off = 0;
			file->line_nb++;
		}
		else
			error_func_ln(file, UNEXP_EOF, NULL);
		ft_printf("%s %d %d %d\n", file->prog_comment, file->glob_off, file->inline_off, file->line_nb);
	}
	else
		error_command(file, data);
	return (0);
}

int		get_cmds(t_file *file, char *data)
{
	while (1)
	{
		file->inline_off = skip_whitespaces(data, file->glob_off);
		if (data[file->glob_off + file->inline_off] == '\n')
		{
			file->glob_off += file->inline_off + 1;
			file->line_nb++;
			file->inline_off = 0;
		}
		else if (data[file->glob_off + file->inline_off] == '.')
			check_command(file, data);
		else
			break;
	}
	return (0);
}

int		create_header(t_a *all, t_file *file)
{
	int		magic;
	int		offset;

	magic = little_to_big_endian(COREWAR_EXEC_MAGIC);
	file->header = ft_memalloc(all->header_size);
	ft_memcpy(file->header, &magic, 4);
	offset = 4;
	get_cmds(file, file->s_file_content);
	if (!file->prog_name)
		return (error_func(all->file, NAME_NOT_FOUND));
	if (!file->prog_comment)
		return (error_func(all->file, COMMENT_NOT_FOUND));
	if (ft_strlen(file->prog_name) > PROG_NAME_LENGTH)
		return (error_func(all->file, NAME_TOO_LONG));
	if (ft_strlen(file->prog_comment) > COMMENT_LENGTH)
		return (error_func(all->file, COMMENT_TOO_LONG));
	ft_memcpy(file->header + offset, file->prog_name, ft_strlen(file->prog_name));

	return (0);
}

int		read_file(t_file *file)
{
	int ret;

	if ((file->s_fd = open(file->s_name, O_RDONLY)) == -1)
		return (error_func(file, OPEN_FAIL));
	file->file_size = lseek(file->s_fd, 0, SEEK_END);
	lseek(file->s_fd, 0, SEEK_SET);
	file->s_file_content = malloc(file->file_size);
	ret = read(file->s_fd, file->s_file_content, file->file_size);
	close(file->s_fd);
	return (ret < 0 ? -1 : 0);
}

int		write_file(t_file *file, char *file_name)
{
	if (!file_name)
		return (-1);
	if ((file->cor_fd = open(file_name, O_WRONLY | O_CREAT, 0755)) == -1)
	{
		ft_printf("%s open failed\n%>", file_name, 2);
		return (-1);
	}
	write(file->cor_fd, file->header, file->file_size);
	close(file->cor_fd);
	return (0);
}

int		create_file(t_a *all, char *file_name)
{
	all->file->s_name = file_name;
	if (ft_strcmp(get_ext(all->file->s_name), "s"))
		return (error_func(all->file, NOT_S_FILE));
	if (read_file(all->file) == -1)
		return (-1);
	if (create_header(all, all->file) == -1)
		return (-1);
	return (write_file(all->file, get_cor_name(file_name)));
}

int		create_files(int ac, char **av, t_a *all)
{
	int		i;

	if (ac < 2)
		exit_func(-1, 1, all);
	i = get_flags(ac, av, all) - 1;
	while (++i < ac)
	{
		all->nb_files_created += create_file(all, av[i]) + 1;
		if (!all->flags[0])
			break ;
	}
	return (0);
}

int		instantiate_all(t_a *all, t_file *file)
{
	ft_bzero(file, sizeof(t_file));
	ft_bzero(all, sizeof(t_a));
	all->header_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	all->flags = malloc(sizeof(OP));
	all->file = file;
	return (0);
}

int		main(int ac, char **av)
{
	t_a		all;
	t_file	file;

	instantiate_all(&all, &file);
	create_files(ac, av, &all);
	ft_printf("nb_files_created %d\n", all.nb_files_created);
	exit_func(0, 0, &all);
}
