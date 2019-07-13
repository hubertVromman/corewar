/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:16:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/13 15:39:20 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		dump_memory()
{
	int		i;

	char *s = malloc(MEM_SIZE * 3);
	char *buffer;
	i = -1;
	while (++i < MEM_SIZE)
	{
		ft_printf("%.2hhx%c%#>", g_all.arena[i], (i + 1) % 64 ? ' ' : '\n', &buffer);
		memcpy(s + i * 3, buffer, 3);
	}
	write(1, s, MEM_SIZE * 3);
	return (0);
}

int		dump_memory_colored()
{
	int		i;
	int		j;
	int		c;

	char *s = malloc(MEM_SIZE * 3 + g_all.nb_champ * 9);
	char *buffer;
	i = -1;
	j = 0;
	while (++i < MEM_SIZE)
	{
		c = -1;
		while (++c < g_all.nb_champ)
		{
			if (i == g_all.champ[c].proces->pc)
			{
				ft_printf("\x1b[%dm%#>", 31 + c, &buffer);
				memcpy(s + i * 3 + j, buffer, 5);
				j += 5;
			}
		}
		ft_printf("%.2hhx%c%#>", g_all.arena[i], (i + 1) % 64 ? ' ' : '\n', &buffer);
		memcpy(s + i * 3 + j, buffer, 3);
		c = -1;
		while (++c < g_all.nb_champ)
		{
			if (i == g_all.champ[c].proces->pc + g_all.champ[c].exec_size)
			{
				ft_printf("\x1b[%dm%#>", 0, &buffer);
				memcpy(s + (i + 1) * 3 + j, "\x1b[0m", 4);
				j += 4;
			}
		}
	}
	write(1, s, MEM_SIZE * 3 + g_all.nb_champ * 9);
	return (0);
}
