/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:31:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/03 18:30:09 by sofchami         ###   ########.fr       */
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

enum	e_error_code { NOT_COR_FILE = 1, OPEN_FAIL, TOO_LARGE, READ_ERROR, INVALID_NB};

enum	e_flag_nb {FORCE_LAUNCH, VISU, INFORMATION};

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
# define HOME_CURSOR "\e[H"

# define MERROR -2

# define P1_COLOR 0x008080
# define P2_COLOR 0x800000
# define P3_COLOR 0xEB34DB
# define P4_COLOR 0x000080
# define COLOR_INCREMENT 0x00010101

# define BORDER_COLOR 0xA8A8A8
# define VM_COLOR 0x787878
# define WHITE 0xffffff
# define COREWAR_COLOR 0x999999

# define OP "fvi"

# define NC "\e[0m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define MAGENTA "\e[35m"
# define CYAN "\e[36m"
# define BOLD_WHITE "\033[1m\033[37m"

# define HEADER_HEIGHT 10
# define MEMORY_HEIGHT 64
# define MEMORY_OFFSET_X 4
# define FLAME_HEIGHT 18
# define MAX_NAME_LENGTH 34
# define PROCES_HEIGHT (MEMORY_HEIGHT - 21) // a changer

# define INFO_WIDTH 104
# define EFFECTIVE_INFO_WIDTH (INFO_WIDTH - 8)

# define S_LIVE 1
# define S_DEATH 2
# define S_FLAME 3

# define SCREEN_HEIGHT (MEMORY_HEIGHT + HEADER_HEIGHT + 1)
# define SCREEN_WIDTH (MEMORY_OFFSET_X + 64 * 3 + 2 + INFO_WIDTH)

# define NUMBER_WIDTH 6

# define NB_OPERATIONS (int)(sizeof(g_op_tab) / sizeof(t_op) - 1)

# define SIZE_ANIM_X 20
# define SIZE_ANIM_Y 8
# define DECO_1 L"°º¤ø,¸¸,ø¤º°`"
# define DECO_2 L"¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤"

typedef struct	s_endscreen
{
	int		ullx;
	int		ulmx;
	int		urmx;
	int		urrx;
	int		ruux;
	int		rumx;
	int		rbmx;
	int		rbbx;
	int		brrx;
	int		brmx;
	int		blmx;
	int		bllx;
	int		lbbx;
	int		lbmx;
	int		lumx;
	int		luux;
	int		ully;
	int		ulmy;
	int		urmy;
	int		urry;
	int		ruuy;
	int		rumy;
	int		rbmy;
	int		rbby;
	int		brry;
	int		brmy;
	int		blmy;
	int		blly;
	int		lbby;
	int		lbmy;
	int		lumy;
	int		luuy;
	int		cx;
	int		cy;
	int		*ray_lines[16];
}				t_endscreen;

typedef struct	s_queu
{
	int			id;
	int			player;
}				t_queu;

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
}				t_proces;

struct			s_champ
{
	int			nb_proces;
	int			lives_period;
	int			index_player;
	int			nb_errors;
	int			exec_size;
	int			last_live;
	int			player_nb;
	int			player_nb_arena;
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
	int			screen_size;
	int			nb_frames_to_skip;
	int			flame;
	int			offset_memory_x;
	int			offset_memory_y;
	int			offset_flame_y;
	char		*feu;
	int			previous_pos;
	int			previous_fg;
	int			previous_bg;
	int			size_aff;
	char		*aff_string;
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
	int			cycle;
	int			pos_depart;
	t_champ		champ[4];
	int			ctd;
	int			len_queu;
	int			nb_errors;
	int			arglen;
	int			id_proces;
	int			nb_proces_tot;
	int			max_proces;
	int			check;
	int			end;
	int			lives_period_tot;
	int			dump_period;
	int			next_champ_nb;
	int			*id_queu;
	int			*player_queu;
	char		*buf;
	int			player_last_live;
	int			(*func[NB_OPERATIONS]) (t_champ *champ, t_proces *proces, t_arg *args);
	char		flags[sizeof(OP)];
	char		arena[MEM_SIZE];
	int			color[MEM_SIZE];
	time_t		sound;
	t_queu		*queu;
	t_visu		visu;
	t_endscreen	end_screen;
}				t_a;

t_a				g_all;

int fd;

/*
** error.c
*/
int				error_func(t_champ *champ, int error_code);

/*
** exit.c
*/
int				exit_func(int exit_code, int dp_usage);
int				free_all(void);
int				usage(void);

/*
** util.c
*/
int				calc_pc(int pc);
int				dump_memory();
int				get_cycle_left(int opcode);
int				play_sound(int i);
int				read_arena_op(int pc);
int				update_cps();

/*
** proces.c
*/
int				create_proces(int pc, t_proces *parent, t_champ *champ);
int				delete_proces(t_champ *champ, int id_proces);
int				reset_proc();


/*
** main.c
*/
int				display_start();
int				parse_arg(int ac, char **av);

/*
** arguments.c
*/
t_arg			*get_arguments(t_proces *proces);

/*
** IO_arena.c
*/
int				increment_pc(t_proces *proces, int nb_byte);
int				read_byte(int pc, int size);
int				write_byte(t_proces *proces, int address, char to_write);
int				write_int(t_proces *proces, int address, int to_write);

/*
** champ_instance.c
*/
int				get_champ(char *file_name);

/*
** lecteur.c
*/
int 			add_to_que(t_proces *proces, int player);
int				beg_battle();
int	 			read_proces();
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
int				jump_to_buf(int pc);

/*
** print_visu.c
*/
int				copy_and_print_buffer(t_printable *dst, t_printable *src, int size);
int				insta_print_char(char c, int f_color, int b_color, int pos);
int				print_char(t_printable printable, int pos);
int				insta_print_string(char *s, int f_color, int b_color, int pos);
int				print_frame_diff();

/*
** print_info.c
*/
int				print_player_info(int k);
int				print_init_info(int i, int lives);
int				print_vm_info();

/*
** util_visu.c
*/
int				add_str_to_buffer(t_printable *strct, char *str, int f_color, int b_color);
int				add_name_to_buffer(t_printable *strct, char *str, int f_color, int b_color);
int				write_to_buf(t_printable *strct, char c, int f_color, int b_color);

/*
** init.c
*/
int				init_all(int ac, char **av, int i);

/*
** thread.c
*/

void			*reader_func(void *rien);
void			*sound_feu();
void			*th_feu();
void			*th_calcul();

/*
** init_visu.c
*/
int				init_visu();

/*
** filler.c
*/
int				fill_border();
int				fill_header();
int				fill_memory();
int				fill_player_info();
int				fill_process_info();

/*
** ray.c
*/
int				create_lines();
int				display_ray();

/*
** init_frame.c
*/

int				fill_current_frame(void);
int				invert_fore_and_back(t_printable *printable);
int				init_current_frame(void);


#endif
