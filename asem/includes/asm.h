/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:30:52 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/06 14:30:59 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "common.h"

# define OP "m"

enum	e_error_code { NOT_S_FILE = 1, OPEN_FAIL, NOT_CREATE, NAME_NOT_FOUND,
	NAME_TOO_LONG, COMMENT_NOT_FOUND, COMMENT_TOO_LONG};

enum	e_ln_error_code { CMD_NOT_FOUND = 101, UNEXP_EOF, TWO_CMD};

typedef struct s_label t_label;

struct			s_label
{
	int		pos;
	char	*name;
	char	content;
	t_label	*next;
};

typedef struct	s_param
{
	int		size;
	int		kind;
	int		inline_off;
	char	*data;
}				t_param;

typedef struct s_instr t_instr;

struct			s_instr
{
	int		index;
	int		size;
	int		pos_in_file;
	int		line_nb;
	char	codage;
	int		nb_params;
	t_param	params[MAX_ARGS_NUMBER];
	t_instr	*next;
};

typedef struct	s_file
{
	char	*header;
	char	*cor_name;
	int		cor_fd;
	char	*s_name;
	int		s_fd;
	int		file_size;
	char	*s_file_content;
	char	*prog_name;
	char	*prog_comment;
	int		glob_off;
	int		line_nb;
	int		inline_off;
	int		nb_error;
	int		offset_;
	int		prog_size;
	char	*prog_content;
	t_label	*labels;
	t_label	*current_lab;
	t_instr	*instr;
	t_instr	*current_instr;
}				t_file;

typedef struct	s_a
{
	int		nb_files_created;
	char	*flags;
	int		header_size;
	t_file	*file;
}				t_a;

/*
** error.c
*/
int				error_func(t_file *file, int error_code);
int				error_func_ln(t_file *file, int code, char *det, int to_free);
int				wrong_char(t_file *file, char *expected, int sub_off);
int				error_command(t_file *file, char *data);

/*
** exit.c
*/
int				free_all(t_a *all);
int				usage(void);
int				exit_func(int exit_code, int dp_usage, t_a *all);

/*
** util.c
*/
char			*get_ext(char *str);
char			*get_cor_name(char *file);
int				little_to_big_endian(int little);
int				skip_whitespaces(char *data, int offset);
int				end_of_line(t_file *file);

/*
** io.c
*/
int				read_file(t_file *file);
int				write_file(t_a *all, t_file *file, char *file_name);

/*
** header.c
*/
int				create_header(t_a *all, t_file *file);

/*
** body.c
*/
int				create_code(t_a *all, t_file *file);

#endif
