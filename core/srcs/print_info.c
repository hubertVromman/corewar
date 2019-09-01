/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 02:28:56 by sofchami          #+#    #+#             */
/*   Updated: 2019/09/01 07:04:30 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_proces_info2(int n, int k,int l, int i)
{
	int stop;
	int opcode;
	char *str;

	str = "  player_nb %5d  |  pc %.4d  |  opcode " CHAR_HEX_PRINT "  |  Name OP %5s  |  cycle_left %.4d%#>";
	stop = 0;
	opcode = g_all.champ[n].proces[k].opcode;
	if (ft_printf(str, g_all.champ[n].player_nb, g_all.champ[n].proces[k].pc,
		opcode, opcode > 0 && opcode <= NB_OPERATIONS ?
		g_op_tab[opcode - 1].name : "null", g_all.champ[n].proces[k].cycle_left,
		&g_all.buf) == -1)
		exit_func(MERROR, 0);
	add_str_to_buffer(g_all.visu.next_frame +
		(g_all.visu.nb_cols * (i + l + k)) + (COL_INFO), g_all.buf, g_all.champ[n].proces[k].color_rgb, 0);
	free(g_all.buf);
	stop++;
	return (stop);
}

int		print_proces_info(int i)
{
	int k;
	int n;
	int l;
	int stop;

	n = -1;
	l = 0;
	stop = 0;
	jump_to(COL_INFO, i);
	while (++n < g_all.nb_champ && stop < PROCES_HEIGHT && (k = -1))
	{
		while (++k < g_all.champ[n].nb_proces && stop < PROCES_HEIGHT)
		{
			stop += print_proces_info2(n, k, l, i);
		}
		l += k;
	}
	return (0);
}

int		print_player_info(int k)
{
	int lines;
	int col;
	while (++k < g_all.nb_champ)
	{
		lines = HEADER_HEIGHT + 9 + (k % 2 ? 5 : 0);
		col = COL_INFO + (k < 2 ? 36 : 84);
		if (ft_printf("%6d%#>", g_all.champ[k].last_live, &g_all.buf) == -1)
			exit_func(MERROR, 0);
		add_str_to_buffer(g_all.visu.next_frame +
			(g_all.visu.nb_cols * lines + col), g_all.buf, WHITE, 0);
		free(g_all.buf);
		if (ft_printf("%6d%#>", g_all.champ[k].lives_period, &g_all.buf) == -1)
			exit_func(MERROR, 0);
		add_str_to_buffer(g_all.visu.next_frame +
			(g_all.visu.nb_cols * (lines + 1) + col), g_all.buf, WHITE, 0);
		free(g_all.buf);
		if (ft_printf("%6d%#>", g_all.champ[k].nb_proces, &g_all.buf) == -1)
			exit_func(MERROR, 0);
		add_str_to_buffer(g_all.visu.next_frame +
			(g_all.visu.nb_cols * (lines + 2) + col), g_all.buf, WHITE, 0);
		free(g_all.buf);
	}
	return (0);
}

int		print_init_info(int i, int lives)
{
	while (++i < g_all.nb_champ)
		lives += g_all.champ[i].lives_period;
	if (ft_printf("%6d%#>", g_all.cycle, &g_all.buf) == -1)
		exit_func(MERROR, 0);
	add_str_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols *
		(HEADER_HEIGHT + 1)) + (COL_INFO + 20), g_all.buf, WHITE, 0);
	ft_strdel(&g_all.buf);
	if (ft_printf("%6d%#>", g_all.nb_proces_tot, &g_all.buf) == -1)
		exit_func(MERROR, 0);
	add_str_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols *
		(HEADER_HEIGHT + 3)) + (COL_INFO + 20), g_all.buf, WHITE, 0);
	ft_strdel(&g_all.buf);
	if (ft_printf("%6d%#>", lives, &g_all.buf) == -1)
		exit_func(MERROR, 0);
	add_str_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols *
		(HEADER_HEIGHT + 4)) + (COL_INFO + 20), g_all.buf, WHITE, 0);
	ft_strdel(&g_all.buf);
	if (ft_printf("%6d%#>", g_all.cycle_to_die, &g_all.buf) == -1)
		exit_func(MERROR, 0);
	add_str_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols *
		(HEADER_HEIGHT + 5)) + (COL_INFO + 20), g_all.buf, WHITE, 0);
	ft_strdel(&g_all.buf);
	print_player_info(-1);
	return (0);
}

int		print_vm_info()
{
	int tmp;

	print_init_info(-1, 0);
	print_proces_info(30);
	if (g_all.max_proces <= g_all.nb_proces_tot)
		g_all.max_proces = g_all.nb_proces_tot;
	else
	{
		tmp = g_all.nb_proces_tot + 19;
		while (tmp <= g_all.max_proces + 19 && tmp > SCREEN_HEIGHT)
		{
			if (ft_printf("%1$/95c%#>", ' ', &g_all.buf) == -1)
				exit_func(MERROR, 0);
			add_str_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols *
				(tmp)) + (COL_INFO), g_all.buf, WHITE, 0);
			free(g_all.buf);
			jump_to(COL_INFO, tmp);
			ft_printf("%1$/95c", ' ');
			tmp++;
		}
		g_all.max_proces = g_all.nb_proces_tot;
	}
	return (0);
}
