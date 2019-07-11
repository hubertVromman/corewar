/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:16:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/11 16:50:31 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		dump_memory()
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (g_all.arena[i])
			ft_printf("<green>%.2hhx%c</>", g_all.arena[i], (i + 1) % 64 ? ' ' : '\n');
		else
			ft_printf("%.2hhx%c", g_all.arena[i], (i + 1) % 64 ? ' ' : '\n');
	}
	return (0);
}
