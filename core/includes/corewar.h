/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:31:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/18 01:43:44 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "common.h"
#include <stdio.h>

enum	e_error_code { NOT_COR_FILE = 1, OPEN_FAIL, TOO_LARGE, READ_ERROR};

# define MERROR -2

# define OP "fv"

# define NC "\x1b[0m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"

# define MAX_PLAYER_NB 6

typedef struct s_proces	t_proces;

struct			s_proces
{
	int			carry;
	int			dead;
	int			pc;
	int			reg[REG_NUMBER];
	int			cycle_left;
	int			id_proces;
	int			opcode;
	int 		arguments[4];
	t_op 		*operations;
	int			lives_period;
	t_proces	*next;
}				;

/*
** liste chainé de tout les proces par joureur. Du coup j'ai
** rajouté la struc op vue que c'est de la qu'on fais passer les instructions.
** Par contre je capte pas les cycle dans la struc des OP.
*/

typedef struct	s_champ
{
	int			nb_proces;
	int			lives_period;
	int			nb_errors;
	int			exec_size;
	int			last_live;
	int			player_nb;
	t_proces	*proces;
	char		*file_name;
	char		*file;
	char		*exec_file;
	char		*player_name;
	char		*comment;
	size_t		file_size;
}				t_champ;

typedef struct	s_a
{
	size_t		header_size;
	int			nb_champ;
	int			cycle_to_die;
	int			pos_depart;
	t_champ		champ[4];
	int			nb_errors;
	int			nbr_processes;
	int			cycle;
	int			dump_period;
	int			next_champ_nb;
	char		flags[sizeof(OP)];
	char		arena[MEM_SIZE];
}				t_a;

t_a				g_all;

typedef struct	s_arg
{
	int		size;
	int		value;
	int		type;
}				t_arg;

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
int				get_cycle_left(int opcode);
int				dump_memory();
int				dump_memory_colored();

/*
** operations.c
*/
int				operation_fork(t_champ *champ, int num_proces);

/*
** main.c
*/
t_proces		*init_proces(int pc, t_proces *parent, int player_nb);

/*
** util_instr.c
*/
t_arg			*get_arguments(int *pc);

/*
** champ_instance.c
*/
int				get_champ(char *file_name);

#endif
