/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 17:22:58 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/12 20:34:44 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		free_all(void)
{
	int		i;

	i = -1;
	while (++i < 16)
		free(g_all.end_screen.ray_lines[i]);
	free(g_all.visu.flame_buf);
	free(g_all.visu.current_frame);
	free(g_all.visu.next_frame);
	free(g_all.visu.current_frame_flame);
	free(g_all.visu.feu);
	return (0);
}

int		usage(void)
{
	ft_printf("usage: corewar [-%s] [-dump dump_period] [[-n player_nb] file.cor] ...\n%>", OP, 2);
	ft_printf("    -v    : Start game in nCurses, disable -dump option\n%>", 2);
	ft_printf("            Screen size must be minimum %dx%d\n%>", SCREEN_WIDTH, SCREEN_HEIGHT, 2);
	ft_printf("    -n    : Set the next player's number "
	"(default is next available) (number is reduce to < 1000)\n%>", 2);
	ft_printf("    -dump : Dump memory in hexadecimal every dump_period\n%>", 2);
	ft_printf("    -i    : Display live and aff informations when not in visu\n%>", 2);
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
		ft_printf("exit\n");
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
