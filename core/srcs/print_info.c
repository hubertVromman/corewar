/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 02:28:56 by sofchami          #+#    #+#             */
/*   Updated: 2019/09/04 23:19:06 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	print_proces_info2(int player_nb, int proc, int proc_tot)
{
	int		opcode;
	char	*str;
	int		offset_y;

	offset_y = HEADER_HEIGHT + 22;
	str = "->  proces_id %6d  |  pc %4d  |  opcode " CHAR_HEX_PRINT
		"  |  Name OP %5s  |  cycle_left %4d%#>";
	opcode = g_all.champ[player_nb].proces[proc].opcode;
	if (ft_printf(str, g_all.champ[player_nb].proces[proc].id_proces,
		g_all.champ[player_nb].proces[proc].pc, opcode, opcode > 0 &&
		opcode <= NB_OPERATIONS ? g_op_tab[opcode - 1].name : "null",
		g_all.champ[player_nb].proces[proc].cycle_left, &g_all.buf) < 0)
		exit_func(MERROR, 0);
	add_str_to_buf(g_all.visu.next_frame +
		(g_all.visu.nb_cols * (offset_y + proc_tot + proc)) - INFO_WIDTH
			+ 4, g_all.buf, g_all.champ[player_nb].color_rgb, 0);
	free(g_all.buf);
	return (0);
}

static int	print_proces_info(void)
{
	int		k;
	int		n;
	int		proc_tot;

	n = -1;
	proc_tot = 0;
	while (++n < g_all.nb_champ && proc_tot <= PROCES_HEIGHT)
	{
		k = -1;
		while (++k < g_all.champ[n].nb_proces && proc_tot + k <= PROCES_HEIGHT)
		{
			print_proces_info2(n, k, proc_tot);
		}
		proc_tot += k;
	}
	return (0);
}

static int	print_player_info(int k)
{
	int		lines;
	int		col;

	while (++k < g_all.nb_champ)
	{
		lines = HEADER_HEIGHT + 10 + (k % 2 ? 5 : 0);
		col = g_all.visu.nb_cols - INFO_WIDTH + 4 + (k < 2 ? 36 : 85);
		if (ft_printf("%6d%#>", g_all.champ[k].last_live, &g_all.buf) < 0)
			exit_func(MERROR, 0);
		add_str_to_buf(g_all.visu.next_frame +
			(g_all.visu.nb_cols * lines + col), g_all.buf, WHITE, 0);
		free(g_all.buf);
		if (ft_printf("%6d%#>", g_all.champ[k].lives_period, &g_all.buf) < 0)
			exit_func(MERROR, 0);
		add_str_to_buf(g_all.visu.next_frame +
			(g_all.visu.nb_cols * (lines + 1) + col), g_all.buf, WHITE, 0);
		free(g_all.buf);
		if (ft_printf("%6d%#>", g_all.champ[k].nb_proces, &g_all.buf) < 0)
			exit_func(MERROR, 0);
		add_str_to_buf(g_all.visu.next_frame +
			(g_all.visu.nb_cols * (lines + 2) + col), g_all.buf, WHITE, 0);
		free(g_all.buf);
	}
	return (0);
}

static int	print_init_info(int i, int lives)
{
	t_printable		*st_point;

	st_point = g_all.visu.next_frame + (g_all.visu.nb_cols *
			(HEADER_HEIGHT + 3)) - INFO_WIDTH + 26;
	while (++i < g_all.nb_champ)
		lives += g_all.champ[i].lives_period;
	if (ft_printf("%*d%#>", NUM_WIDTH, g_all.cycle, &g_all.buf) < 0)
		exit_func(MERROR, 0);
	add_str_to_buf(st_point, g_all.buf, WHITE, 0);
	ft_strdel(&g_all.buf);
	if (ft_printf("%*d%#>", NUM_WIDTH, g_all.nb_proces_tot, &g_all.buf) < 0)
		exit_func(MERROR, 0);
	add_str_to_buf(st_point + g_all.visu.nb_cols * 2, g_all.buf, WHITE, 0);
	ft_strdel(&g_all.buf);
	if (ft_printf("%*d%#>", NUM_WIDTH, lives, &g_all.buf) < 0)
		exit_func(MERROR, 0);
	add_str_to_buf(st_point + g_all.visu.nb_cols * 3, g_all.buf, WHITE, 0);
	ft_strdel(&g_all.buf);
	if (ft_printf("%*d%#>", NUM_WIDTH, g_all.cycle_to_die, &g_all.buf) < 0)
		exit_func(MERROR, 0);
	add_str_to_buf(st_point + g_all.visu.nb_cols * 4, g_all.buf, WHITE, 0);
	ft_strdel(&g_all.buf);
	print_player_info(-1);
	return (0);
}

int			print_vm_info(void)
{
	int i;

	print_init_info(-1, 0);
	print_proces_info();
	if (g_all.max_proces <= g_all.nb_proces_tot)
		g_all.max_proces = g_all.nb_proces_tot;
	else
	{
		i = g_all.nb_proces_tot + HEADER_HEIGHT + 22;
		while (i <= g_all.max_proces + HEADER_HEIGHT + 22 && i < SCREEN_HEIGHT)
		{
			if (ft_printf("%1$/95c%#>", ' ', &g_all.buf) < 0)
				exit_func(MERROR, 0);
			add_str_to_buf(g_all.visu.next_frame + g_all.visu.nb_cols * i -
				INFO_WIDTH + 4, g_all.buf, WHITE, 0);
			free(g_all.buf);
			i++;
		}
		g_all.max_proces = g_all.nb_proces_tot;
	}
	return (0);
}
