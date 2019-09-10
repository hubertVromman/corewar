/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 17:22:58 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/10 05:48:01 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		add_to_que(int player, int proces)
{
	if (!(g_all.queu = realloc(g_all.queu, sizeof(t_pp) *
		(g_all.len_queu + 1))))
		exit_func(MERROR, 0);
	g_all.queu[g_all.len_queu].player = player;
	g_all.queu[g_all.len_queu].proces = proces;
	g_all.len_queu++;
	return (0);
}

int		free_all(void)
{
	int		i;

	i = -1;
	while (++i < 16)
		free(g_all.end_screen.ray_lines[i]);
	i = -1;
	while (++i < 4)
	{
		free(g_all.champ[i].file);
		free(g_all.champ[i].proces);
	}
	free(g_all.visu.flame_buf);
	free(g_all.visu.current_frame);
	free(g_all.visu.next_frame);
	free(g_all.visu.current_frame_flame);
	free(g_all.visu.feu);
	free(g_all.visu.aff_s);
	free(g_all.queu);
	return (0);
}

int		usage(void)
{
	ft_printf(
	"usage: corewar [-%s] [-dump dump_period] [[-n player_nb] file.cor] ...\n"
	"    -v    : Start game in nCurses, disable -dump option\n"
	"            Screen size must be minimum %dx%d\n"
	"    -n    : Set the next player's number "
	"(default is next available) (number is reduce to < 1000)\n"
	"    -dump : Dump memory in hexadecimal every dump_period\n"
	"    -s    : Silence all sound when in visu\n"
	"    -i    : Display live and aff informations when not in visu\n%>",
		OP, SCREEN_WIDTH, SCREEN_HEIGHT, 2);
	return (0);
}

int		exit_func(int exit_code, int dp_usage)
{
	if (g_all.flags[VISU])
	{
		pthread_cancel(g_all.visu.thread_calcul);
		pthread_cancel(g_all.visu.thread_flamme);
		pthread_cancel(g_all.visu.thread_reader);
		pthread_cancel(g_all.visu.thread_sound);
	}
	if (!dp_usage && g_all.flags[VISU])
	{
		ft_printf(RESTORE_SCREEN);
		ft_printf(RESET_COLOR);
		ft_printf(UNHIDE_CURSOR);
	}
	if (dp_usage)
		usage();
	if (exit_code == -2)
		ft_printf("malloc error\n%>", 2);
	if (!exit_code && g_all.nb_errors)
		exit_code = g_all.nb_errors;
	system("pkill afplay");
	free_all();
	exit(exit_code);
}
