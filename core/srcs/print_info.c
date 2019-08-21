/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 02:28:56 by sofchami          #+#    #+#             */
/*   Updated: 2019/08/20 23:54:16 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_reg_info(t_proces *proces)
{
	jump_to(X - 70, HEADER_HEIGHT);
	ft_printf("Id proces = %d", proces->id_proces);
	jump_to(X - 70, HEADER_HEIGHT + 1);
	ft_printf("reg 0  : %10d | reg 1  : %10d | reg 2  : %10d", proces->reg[0],proces->reg[1], proces->reg[2]);
	jump_to(X - 70, HEADER_HEIGHT + 2);
	ft_printf("reg 3  : %10d | reg 4  : %10d | reg 5  : %10d", proces->reg[3],proces->reg[4], proces->reg[5]);
	jump_to(X - 70, HEADER_HEIGHT + 3);
	ft_printf("reg 6  : %10d | reg 7  : %10d | reg 8  : %10d", proces->reg[6],proces->reg[7], proces->reg[8]);
	jump_to(X - 70, HEADER_HEIGHT + 4);
	ft_printf("reg 9  : %10d | reg 10 : %10d | reg 11 : %10d", proces->reg[9],proces->reg[10], proces->reg[11]);
	jump_to(X - 70, HEADER_HEIGHT + 5);
	ft_printf("reg 12 : %10d | reg 13 : %10d | reg 14 : %10d", proces->reg[12],proces->reg[13], proces->reg[14]);
	return (0);
}

// int		print_border_side()
// {
// 	int i;

// 	i = -1;
// 	while (++i < g_all.visu.nb_lines - 8)
// 	{
// 		jump_to(g_all.visu.nb_cols - 1, i);
// 		ft_printf(RGB_PRINT_BG "%c", (BORDER_COLOR >> 16) & 0xff, (BORDER_COLOR >> 8) & 0xff,(BORDER_COLOR >> 0) & 0xff, ' ');
// 		jump_to(0, i);
// 		ft_printf(RGB_PRINT_BG "%c", (BORDER_COLOR >> 16) & 0xff, (BORDER_COLOR >> 8) & 0xff,(BORDER_COLOR >> 0) & 0xff, ' ');
// 	}
// 	return (0);
// }

int		print_border()
{
	int i;

	i = -1;
	while (++i < SCREEN_HEIGHT) // vertical lines
	{
		write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * (i + 1) - 1, ' ', 0, BORDER_COLOR);
		write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * (i + 1) - 2, ' ', 0, BORDER_COLOR);
		if (i >= HEADER_HEIGHT - 2)
		{
			write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * (i + 1) - 102, ' ', 0, BORDER_COLOR);
			write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * (i + 1) - 103, ' ', 0, BORDER_COLOR);
		}
		write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * i, ' ', 0, BORDER_COLOR);
		write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * i + 1, ' ', 0, BORDER_COLOR);

	}
	i = -1;
	while (++i < g_all.visu.nb_cols) // horizontal lines
	{
		write_to_buffer(g_all.visu.current_frame + 0 * g_all.visu.nb_cols + i, ' ', 0, BORDER_COLOR);
		write_to_buffer(g_all.visu.current_frame + 8 * g_all.visu.nb_cols + i, ' ', 0, BORDER_COLOR);
		write_to_buffer(g_all.visu.current_frame + SCREEN_HEIGHT * g_all.visu.nb_cols + i, ' ', 0, BORDER_COLOR);
	}
	return (0);
}

int		print_header()
{
	int		offset_x;

	offset_x = g_all.visu.nb_cols / 2 - 21;
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 1, "   _____                                  ", 0x999999, 0);
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 2, "  / ____|                                 ", 0x999999, 0);
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 3, " | |     ___  _ __ _____      ____ _ _ __ ", 0x999999, 0);
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 4, " | |    / _ \\| '__/ _ \\ \\ /\\ / / _` | '__|", 0x999999, 0);
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 5, " | |___| (_) | | |  __/\\ V  V / (_| | |   ", 0x999999, 0);
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 6, "  \\_____\\___/|_|  \\___| \\_/\\_/ \\__,_|_|   ", 0x999999, 0);
	return (0);
}

int		print_proces_info(int i)
{
	int k;
	int n;
	int l;
	int stop;
	int opcode;

	n = -1;
	l = 0;
	stop = 0;
	jump_to(X, i);
	while (++n < g_all.nb_champ && stop < PROCES_HEIGHT)
	{
		k = -1;
		while (++k < g_all.champ[n].nb_proces && stop < PROCES_HEIGHT)
		{
			// if (i + k + l > g_all.visu.nb_lines - 20)
			// 	return (0);
			jump_to(X, i + k + l);
			opcode = g_all.champ[n].proces[k].opcode;
			ft_printf("  player_nb %2d  |  pc %4d  |  opcode " CHAR_HEX_PRINT "  |  Name OP %5s  |  cycle_left %4d\n", g_all.champ[n].player_nb, g_all.champ[n].proces[k].pc, opcode, opcode > 0 && opcode < 17 ? g_op_tab[opcode - 1].name : "null", g_all.champ[n].proces[k].cycle_left);
			stop++;
		}
		l += k;
	}
	return (0);
}

int		print_player_info(int i)
{
	int k;

	k = -1;
	while (++k < g_all.nb_champ)
	{
		i++;
		jump_to(k < 2 ? X + 25 : X + 75,k < 2 ? i : i - 10);
		ft_printf(RESET_COLOR ": %4d", g_all.champ[k].last_live);
		i++;
		jump_to(k < 2 ? X + 25 : X + 75,k < 2 ? i : i - 10);
		ft_printf(RESET_COLOR ": %4d", g_all.champ[k].lives_period);
		i++;
		jump_to(k < 2 ? X + 25 : X + 75,k < 2 ? i : i - 10);
		ft_printf(RESET_COLOR ": %4d", g_all.champ[k].nb_proces);
		i+=2;
	}
	i++;
	return (i);
}

int		print_init_info(int i)
{
	int lives;
	// char *buf = NULL;

	lives = 0;
	while (++i < g_all.nb_champ)
		lives += g_all.champ[i].lives_period;
	ft_printf(RESET_COLOR);
	i = 0;
	while (++i < 6)
	{
		jump_to(X + 20, i + HEADER_HEIGHT);
		i == 1 ? ft_printf(": %4d", g_all.cycle) : 0;
		// i == 2 ? ft_printf("Cycles/second limit : %4d", g_all.visu.max_cps) : 0;
		i == 3 ? ft_printf(": %4d", g_all.nb_proces_tot) : 0;
		i == 4 ? ft_printf(": %4d", lives) : 0;
		i == 5 ? ft_printf(": %4d", g_all.cycle_to_die) : 0;
	}
	i+=HEADER_HEIGHT;
	i++;
	i = print_player_info(i);
	i++;
	return (i);
}

int		print_vm_info()
{
	int i;

	i = print_init_info(-1);
	print_proces_info(30);
	// print_reg_info(g_all.champ[0].proces);
	if (g_all.max_proces <= g_all.nb_proces_tot)
		g_all.max_proces = g_all.nb_proces_tot;
	else
	{
		int tmp;
		tmp = g_all.nb_proces_tot + i;
		while (tmp <= g_all.max_proces + i && tmp > SCREEN_HEIGHT)
		{
			jump_to(X, tmp);
			ft_printf("%1$/95c", ' ');
			tmp++;
		}
		g_all.max_proces = g_all.nb_proces_tot;
	}
	return (0);
}
