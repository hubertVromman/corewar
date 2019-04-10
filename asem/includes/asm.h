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

enum	e_ln_error_code { CMD_NOT_FOUND = 101, UNEXP_EOF};

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
}				t_file;

typedef struct	s_a
{
	int		nb_files_created;
	char	*flags;
	int		header_size;
	t_file	*file;
}				t_a;

#endif
