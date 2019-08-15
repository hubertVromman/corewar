/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:31:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/15 07:07:06 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "common.h"
# include <signal.h>
# include <pthread.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <pthread.h>

enum	e_error_code { NOT_COR_FILE = 1, OPEN_FAIL, TOO_LARGE, READ_ERROR};

enum	e_flag_nb {FORCE_LAUNCH, VISU};

enum	e_opcode { LIVE_OP = 1, LD_OP, ST_OP, ADD_OP, SUB_OP, AND_OP, OR_OP, XOR_OP, ZJMP_OP, LDI_OP, STI_OP, FORK_OP, LLD_OP, LLDI_OP, LFORK_OP, AFF_OP };

# define RESET_COLOR "\e[0m"
# define HIDE_CURSOR "\e[?25l"
# define UNHIDE_CURSOR "\e[?25h"
# define CLEAR_SCREEN "\e[H\e[2J"
# define COLOR_PRINT "\e[%dm"
# define CHAR_HEX_PRINT "%.2hhx"
# define RGB_PRINT "\e[38;2;%.3d;%.3d;%.3dm"
# define RGB_PRINT_BG "\e[48;2;%.3d;%.3d;%.3dm"
# define SAVE_SCREEN "\e[?1049h"
# define RESTORE_SCREEN "\e[?1049l"

# define MERROR -2

# define P1_COLOR 0x00008080
# define P2_COLOR 0x00800000
# define P3_COLOR 0x00EB34DB//0x00800000
# define P4_COLOR 0x00000080
# define BORDER 0x00A8A8A8

# define COLOR_INCREMENT 0x00010101

# define OP "fv"

# define NC "\e[0m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define MAGENTA "\e[35m"
# define CYAN "\e[36m"

# define HEADER_HEIGHT 10
# define MEMORY_OFFSET_X 2
# define FLAME_HEIGHT 18

# define X 265

# define NB_OPERATIONS sizeof(g_op_tab) / sizeof(t_op)

typedef struct	s_printable
{
	char			to_print;
	unsigned int	fore_color : 24;
	unsigned int	back_color : 24;
}				t_printable;

typedef struct	s_arg
{
	int		size;
	int		value;
	int		type;
}				t_arg;

typedef struct	s_champ	t_champ;

typedef struct	s_proces
{
	int			carry;
	int			pc;
	int			cycle_left;
	int			id_proces;
	int			opcode;
	int 		arguments[4];
	int			lives_period;
	int			color_rgb;
	int			reg[REG_NUMBER];
	t_champ		*champ;
}				t_proces;

struct			s_champ
{
	int			nb_proces;
	int			lives_period;
	int			nb_errors;
	int			exec_size;
	int			last_live;
	int			player_nb;
	int			color_rgb;
	t_proces	*proces;
	char		*file_name;
	char		*file;
	char		*exec_file;
	char		*player_name;
	char		*comment;
	size_t		file_size;
};

typedef struct	s_visu
{
	int			pause;
	int			mouse;
	int			max_cps;
	int			nb_cols;
	int			nb_lines;
	int			nb_frames_to_skip;
	int			skipped_frames;
	int			flame;
	int			offset_memory_x;
	int			offset_memory_y;
	int			offset_flame_y;
	char		*feu;
	t_printable	*flame_buf;
	t_printable	*current_frame;
	t_printable	*current_frame_flame;
	t_printable	*next_frame;
	pthread_t	thread_calcul;
	pthread_t	thread_flamme;
	pthread_t	thread_reader;
	pthread_t	thread_sound;
}				t_visu;

typedef struct	s_a
{
	size_t		header_size;
	int			nb_champ;
	int			cycle_to_die;
	int			pos_depart;
	int			ctd;
	t_champ		champ[4];
	int			nb_errors;
	int			id_proces;
	int			nb_proces_tot;
	int			max_proces;
	int			check;
	int			end;
	int			cycle;
	int			dump_period;
	int			next_champ_nb;
	int			player_last_live;
	int			(*func[NB_OPERATIONS]) (t_champ *champ, t_proces *proces, t_arg *args);
	char		flags[sizeof(OP)];
	t_proces	*queu[100];
	t_visu		visu;
	char		arena[MEM_SIZE];
	int			color[MEM_SIZE];
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
int				init_current_frame();

/*
** main.c
*/
int				print_debug_info();
void			*sound_feu();

/*
** util_instr.c
*/
t_arg			*get_arguments(t_proces *proces);
int				calc_pc(int pc);
int				increment_pc(t_proces *proces, int nb_byte);
int				write_byte(t_proces *proces, int address, char to_write);
int				write_int(t_proces *proces, int address, int to_write);
int				read_byte(int pc, int size);

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

/*
** visu.c
*/
void			exit_ctrl_c(int c);
int				jump_to(int x, int y);
int				jump_to_mem(int pc);
int				jump_to_buf(int pc);

/*
** print_info.c
*/
int				print_header();
int				print_proces_info(int i);
int				print_player_info(int i);
int				print_init_info(int i);
int				print_vm_info();
int				print_border();
int				print_border_side();
int				print_reg_info(t_proces *proces);

/*
** util_visu.c
*/
int				write_to_buffer(t_printable *strct, char c, int f_color, int b_color);

#endif
