/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:39:56 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/07 01:37:44 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft.h"
# include "op.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_op
{
	char				*name;
	int					nb_params;
	int					param[MAX_ARGS_NUMBER];
	int					opcode;
	int					cycle_op;
	char				*long_name;
	int					codage;
	int					dir_size;
}					t_op;

t_op				g_op_tab[17];

/*
** util.c
*/
int					change_endianness(int little);
char				*get_ext(char *str);

#endif
