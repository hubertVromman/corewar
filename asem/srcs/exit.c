/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:50:43 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/12 16:50:44 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		free_all(t_a *all)
{
	free(all->flags);
	return (0);
}

int		usage(void)
{
	ft_printf("usage: asm: [-%s] file.s ...\n%>", OP, 2);
	ft_printf("      -m  : Unable to compile multiple files\n%>", 2);
	return (0);
}

int		exit_func(int exit_code, int dp_usage, t_a *all)
{
	if (dp_usage)
		usage();
	free_all(all);
	exit(exit_code);
}
