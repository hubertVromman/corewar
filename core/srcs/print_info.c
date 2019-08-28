/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 02:28:56 by sofchami          #+#    #+#             */
/*   Updated: 2019/08/28 00:32:05 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_proces_info(int i)
{
	int k;
	int n;
	int l;
	int stop;
	int opcode;
	char *tmp;

	tmp = NULL;
	n = -1;
	l = 0;
	stop = 0;
	jump_to(X, i);
	while (++n < g_all.nb_champ && stop < PROCES_HEIGHT)
	{
		k = -1;
		while (++k < g_all.champ[n].nb_proces && stop < PROCES_HEIGHT)
		{
			opcode = g_all.champ[n].proces[k].opcode;
			// jump_to(X, i + k + l);
			if (ft_printf("  player_nb %5d  |  pc %4d  |  opcode " CHAR_HEX_PRINT "  |  Name OP %5s  |  cycle_left %4d%#>", g_all.champ[n].player_nb, g_all.champ[n].proces[k].pc, opcode, opcode > 0 && opcode <= NB_OPERATIONS ? g_op_tab[opcode - 1].name : "null", g_all.champ[n].proces[k].cycle_left, &tmp) == -1)
				exit_func(MERROR, 0);
			add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (i + l + k)) + (X), tmp, 0xffffff, 0);
			free(tmp);
			stop++;
		}
		l += k;
	}
	return (0);
}

int		print_player_info(int i)
{
	int k;
	char *tmp;

	k = -1;
	tmp = NULL;
	while (++k < g_all.nb_champ)
	{
		if (k < 2)
		{
			if (ft_printf(": %4d%#>", g_all.champ[k].last_live, &tmp) == -1)
			exit_func(MERROR, 0);
			add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (HEADER_HEIGHT + 8 + (k % 2 ? 5 : 0))) + (X + 35), tmp, 0xffffff, 0);
			free(tmp);
			if (ft_printf(": %4d%#>", g_all.champ[k].lives_period, &tmp) == -1)
			exit_func(MERROR, 0);
			add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (HEADER_HEIGHT + 9 + (k % 2 ? 5 : 0))) + (X + 35), tmp, 0xffffff, 0);
			free(tmp);
			if (ft_printf(": %4d%#>", g_all.champ[k].nb_proces, &tmp) == -1)
			exit_func(MERROR, 0);
			add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (HEADER_HEIGHT + 10 + (k % 2 ? 5 : 0))) + (X + 35), tmp, 0xffffff, 0);
			free(tmp);
		}
		else
		{
			if (ft_printf(": %4d%#>", g_all.champ[k].last_live, &tmp) == -1)
			exit_func(MERROR, 0);
			add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (HEADER_HEIGHT + 8 + (k % 2 ? 5 : 0))) + (X + 85), tmp, 0xffffff, 0);
			free(tmp);
			if (ft_printf(": %4d%#>", g_all.champ[k].lives_period, &tmp) == -1)
			exit_func(MERROR, 0);
			add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (HEADER_HEIGHT + 9 + (k % 2 ? 5 : 0))) + (X + 85), tmp, 0xffffff, 0);
			free(tmp);
			if (ft_printf(": %4d%#>", g_all.champ[k].nb_proces, &tmp) == -1)
			exit_func(MERROR, 0);
			add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (HEADER_HEIGHT + 10 + (k % 2 ? 5 : 0))) + (X + 85), tmp, 0xffffff, 0);
			free(tmp);
		}
	}
	i++;
	return (i);
}

int		print_init_info(int i)
{
	int lives;
	char *tmp;

	tmp = NULL;
	lives = 0;
	while (++i < g_all.nb_champ)
		lives += g_all.champ[i].lives_period;
	ft_printf(RESET_COLOR);
	i = 0;
	if (ft_printf(": %4d%#>", g_all.cycle, &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (HEADER_HEIGHT + 1)) + (X + 20), tmp, 0xffffff, 0);
	ft_strdel(&tmp);
	if (ft_printf(": %4d%#>", g_all.nb_proces_tot, &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (HEADER_HEIGHT + 3)) + (X + 20), tmp, 0xffffff, 0);
	ft_strdel(&tmp);
	if (ft_printf(": %4d%#>", lives, &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (HEADER_HEIGHT + 4)) + (X + 20), tmp, 0xffffff, 0);
	ft_strdel(&tmp);
	if (ft_printf(": %4d%#>", g_all.cycle_to_die, &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (HEADER_HEIGHT + 5)) + (X + 20), tmp, 0xffffff, 0);
	ft_strdel(&tmp);
	while (++i < 6)
	{
		// jump_to(X + 20, i + HEADER_HEIGHT);
		// i == 1 ? ft_printf(": %4d", g_all.cycle) : 0;
		// i == 2 ? ft_printf("Cycles/second limit : %4d", g_all.visu.max_cps) : 0;
		// i == 3 ? ft_printf(": %4d", g_all.nb_proces_tot) : 0;
		// i == 4 ? ft_printf(": %4d", lives) : 0;
		// i == 5 ? ft_printf(": %4d", g_all.cycle_to_die) : 0;
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
	char *tmp1;

	i = print_init_info(-1);
	print_proces_info(30);
	tmp1 = NULL;
	// print_reg_info(g_all.champ[0].proces);
	if (g_all.max_proces <= g_all.nb_proces_tot)
		g_all.max_proces = g_all.nb_proces_tot;
	else
	{
		int tmp;
		tmp = g_all.nb_proces_tot + i;
		while (tmp <= g_all.max_proces + i && tmp > SCREEN_HEIGHT)
		{
			if (ft_printf("%1$/95c%#>", ' ', &tmp1) == -1)
				exit_func(MERROR, 0);
			add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * (tmp)) + (X), tmp1, 0xffffff, 0);
			free(tmp1);
			// jump_to(X, tmp);
			// ft_printf("%1$/95c", ' ');
			tmp++;
		}
		g_all.max_proces = g_all.nb_proces_tot;
	}
	// print_frame_diff();
	return (0);
}
