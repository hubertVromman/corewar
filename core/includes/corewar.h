/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:31:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/18 21:03:17 by sofchami         ###   ########.fr       */
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

typedef struct	s_arg
{
	int		size;
	int		value;
	int		type;
}				t_arg;

typedef struct	s_champ t_champ;

typedef struct	s_proces
{
	int			carry;
	int			pc;
	int			cycle_left;
	int			id_proces;
	int			opcode;
	int 		arguments[4];
	int			lives_period;
	int			reg[REG_NUMBER];
	t_champ		*champ;
}				t_proces;

/*
** changer proces en array
*/

typedef struct	s_champ
{
	int			nb_proces;
	int			lives_period;
	int			nb_errors;
	int			exec_size;
	int			last_live;
	int			player_nb;
	int			color_id;
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
	int			ctd;
	t_champ		champ[4];
	int			nb_errors;
	int			nb_proces_tot;
	int			cycle;
	int			dump_period;
	int			next_champ_nb;
	int			(*func[16]) (t_champ *champ, t_proces *proces, t_arg *args);
	char		flags[sizeof(OP)];
	char		arena[MEM_SIZE];
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
int				get_cycle_left(int opcode);
int				create_proces(int pc, t_proces *parent, t_champ *champ);
int				detele_proces(t_champ *champ, int id_proces);
int				dump_memory();
int				dump_memory_colored();

/*
** main.c
*/
int				print_debug_info();

/*
** util_instr.c
*/
t_arg			*get_arguments(t_proces *proces);
int				calc_pc(int pc);
int				increment_pc(t_proces *proces, int nb_byte);
int				write_byte(t_proces *proces, int address, char to_write);
int				write_int(t_proces *proces, int address, int to_write);

/*
** champ_instance.c
*/
int				get_champ(char *file_name);

/*
** lecteur.c
*/
int				beg_battle();
int	 			read_proces();
int				reset_proc();
int				read_arena_op(int pc);

/*
** operations
*/
int				operation_add(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_aff(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_and(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_fork(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_ld(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_ldi(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_lfork(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_live(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_lld(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_lldi(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_or(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_st(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_sti(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_sub(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_xor(t_champ *champ, t_proces *proces, t_arg *args);
int				operation_zjmp(t_champ *champ, t_proces *proces, t_arg *args);

#endif
