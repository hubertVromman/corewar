/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 17:22:58 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/11 04:28:28 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		free_all(void)
{
	return (0);
}

int		usage(void)
{
	ft_printf("usage: corewar [-%s] [-dump dump_period] [[-n player_nb] file.cor] ...\n%>", OP, 2);
	ft_printf("    -f    : Start game even if one file error\n%>", 2);
	ft_printf("    -v    : Start game in nCurses, disable -dump\n%>", 2);
	ft_printf("    -n    : Set the next player's number"
	" (default next available)\n%>", 2);
	ft_printf("    -dump : Dump memory in hexadecimal every dump_period\n%>", 2);
	return (0);
}

int		exit_func(int exit_code, int dp_usage)
{
	if (g_all.flags[VISU])
	{
		ft_printf(RESET_COLOR);
		ft_printf("exit\n");
		ft_printf(UNHIDE_CURSOR); //unhide cursor
	}
	if (dp_usage)
		usage();
	if (exit_code == -2)
		ft_printf("malloc error\n%>", 2);
	if (!exit_code && g_all.nb_errors)
		exit_code = g_all.nb_errors;
	free_all();
	pthread_join(g_all.thread_id, NULL);
	exit(exit_code);
}
