/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:31:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/06 14:31:15 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "common.h"

enum	e_error_code { NOT_COR_FILE = 1, OPEN_FAIL};

# define MERROR -2

#define OP "f"

typedef struct	s_champ
{
	char	*file_name;
	char	*file;
	int		nb_errors;
	size_t	file_size;
}				t_champ;

typedef struct	s_a
{
	int		nb_champ;
	t_champ	*champ;
	int		nb_errors;
	char	*flags;
	int		start;
}				t_a;

t_a				g_all;

/*
** error.c
*/
int				error_func(t_champ *champ, int error_code);

/*
** exit.c
*/
int				usage(void);
int				exit_func(int exit_code, int dp_usage);

/*
** util.c
*/
char			*get_ext(char *str);
#endif
