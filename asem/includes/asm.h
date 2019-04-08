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

#define OP "m"

typedef struct	s_file
{
	char	*header;
	char	*cor_name;
	int		cor_fd;
	char	*s_name;
	int		s_fd;
	int		file_size;
	char	*s_file_content;
}				t_file;

typedef struct	s_a
{
	int		nb_files_created;
	char	*flags;
	int		header_size;
	t_file	*file;
}				t_a;

#endif