/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:16:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/27 05:18:42 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_cycle_left(int opcode)
{
	if (opcode < 1 || opcode > NB_OPERATIONS)
	{
		return (1);
	}
	else
		return (g_op_tab[opcode - 1].cycle_op);
}

int		calc_pc(int pc)
{
	return ((pc + MEM_SIZE) % MEM_SIZE);
}

int		read_arena_op(int pc)
{
	int		opcode;

	opcode = g_all.arena[pc];
	if (opcode < 1 || opcode > NB_OPERATIONS)
		return (0);
	return (opcode);
}

int		play_sound(int i)
{
	i = 0;
	// system("pkill afplay &");
	// if (i == 1)
	// system("afplay sound/Ta_da.mp3 &");
	// if (i == 2)
	// system("afplay sound/power_off.mp3 &");
	return (0);
}

int		dump_memory()
{
	int		i;
	char *buffer;
	char *s;

	if (!(s = malloc(MEM_SIZE * 3)))
		exit_func(MERROR, 0);
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (ft_printf(CHAR_HEX_PRINT "%c%#>", g_all.arena[i], (i + 1) % 64 ? ' ' : '\n', &buffer) == -1)
			exit_func(MERROR, 0);
		memcpy(s + i * 3, buffer, 3);
		free(buffer);
	}
	write(1, s, MEM_SIZE * 3);
	free(s);
	return (0);
}

int		update_cps()
{
	// jump_to(X + 20, 2 + HEADER_HEIGHT);
	// ft_printf(": %4d", g_all.visu.max_cps);
	return (0);
}
