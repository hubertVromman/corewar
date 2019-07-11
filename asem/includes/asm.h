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

# define OP "mbo"

enum	e_error_code { NOT_S_FILE = 1, OPEN_FAIL, NOT_CREATE, NAME_NOT_FOUND,
	NAME_TOO_LONG, COMMENT_NOT_FOUND, COMMENT_TOO_LONG};

enum	e_ln_error_code { CMD_NOT_FOUND = 101, UNEXP_EOF, TWO_CMD, WRONG_TYPE,
	NOT_LABEL, INSTR_NOT_FOUND};

enum	e_flag_nb { MULTIPLE_FILES, OTHER_BASE, OPERATION};

typedef struct s_label	t_label;

struct			s_label
{
	int		pos;
	char	*name;
	char	content;
	t_label	*next;
};

typedef struct s_param	t_param;

struct			s_param
{
	int		size;
	int		kind;
	int		base;
	int		line_off;
	char	*data;
	t_param	*extend_op;
};

typedef struct s_instr	t_instr;

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
	char	*s_name;
	int		file_size;
	char	*s_file_content;
	char	*prog_name;
	char	*prog_comment;
	int		glob_off;
	int		line_nb;
	int		line_off;
	int		nb_error;
	int		offset_;
	int		prog_size;
	char	*prog_content;
	int		extend;
	t_label	*labels;
	t_label	*current_lab;
	t_instr	*instr;
	t_instr	*curr_instr;
}				t_file;

typedef struct	s_a
{
	int		nb_files_created;
	char	*flags;
	int		header_size;
	t_file	*file;
	int		nb_errors;
}				t_a;

typedef struct	s_var
{
	int	i;
	int	sub_off;
	int	data_size;
	int	extend_size;
}				t_var;

t_a				g_all;

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
int				free_file(t_file *file);
int				usage(void);
int				exit_func(int exit_code, int dp_usage);

/*
** util.c
*/
char			*get_cor_name(char *file);
int				skip_spaces(char *data, int offset);
int				end_of_line(t_file *file);

/*
** util2.c
*/
int				nb_digits(char *str, int *base);
int				get_normal_base(char *data, int base);

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
** label.c
*/
int				get_label(t_file *file, char *data);
int				label_length(char *str);

/*
** body.c
*/
int				create_code(t_a *all, t_file *file);

/*
** write_instr.c
*/
int				write_params(t_file *file);
int				write_instr(t_file *file);
int				get_label_pos(t_file *file, char *label);

/*
** get_parse_info.c
*/
int				get_name(t_file *file, char *data);

/*
** operation.c
*/
int				get_operations(t_file *file, char *data, int offset,
	t_param *param);
int				get_extend(t_file *file, t_param *param, int pos_in_file);

#endif
