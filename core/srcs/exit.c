/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 17:22:58 by hvromman          #+#    #+#             */
/*   Updated: 2019/06/14 17:23:01 by hvromman         ###   ########.fr       */
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
	ft_printf("    -v    : Start game in nCurses\n%>", 2);
	ft_printf("    -n    : Set the next player's number"
	" (default next available)\n%>", 2);
	ft_printf("    -dump : Dump memory in hexadecimal every dump_period\n%>", 2);
	// 	"(also works with .extend command)\n%>", 2);
	// ft_printf("             0b : binary\n%>", 2);
	// ft_printf("             0  : octal\n%>", 2);
	// ft_printf("             0x : hexadecimal\n%>", 2);
	// ft_printf("      -o  : Unable to perform operations in parameters\n%>", 2);
	return (0);
}

int		exit_func(int exit_code, int dp_usage)
{
	ft_printf("exit\n");
	if (dp_usage)
		usage();
	if (exit_code == -2)
		ft_printf("malloc error\n%>", 2);
	if (!exit_code && g_all.nb_errors)
		exit_code = g_all.nb_errors;
	free_all();
	exit(exit_code);
}
