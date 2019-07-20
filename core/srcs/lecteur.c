/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lecteur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:57:39 by sofchami          #+#    #+#             */
/*   Updated: 2019/07/19 14:13:55 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		read_arena_op(int pc)
{
	int opcode;

	opcode = 0;
	opcode = g_all.arena[pc];
	if (opcode < 1 || opcode > 16)
		return (0);
	return (opcode);
}

int		reset_proc()
{
	int i;
	int total_lives;
	int k;

	i = -1;
	total_lives = 0;
	while (++i < g_all.nb_champ)
	{
		k = -1;
		while (++k < g_all.champ[i].nb_proces)
		{
			if (!g_all.champ[i].proces[k].lives_period)
			{
				ft_printf("------------------------------------------------------------------------------------------------------------\n");
				detele_proces(&g_all.champ[i], k);
				k--;
			}
			else
			{
				total_lives += g_all.champ[i].proces[k].lives_period;
				g_all.champ[i].proces[k].lives_period = 0;
			}
		}
	}
	return (total_lives);
}

int		read_proces()
{
	int i;
	int k;
	t_arg *arg;

	i = -1;
	while (i++ < g_all.nb_champ)
	{
		k = -1;
		while (++k < g_all.champ[i].nb_proces)
		{
			if (g_all.champ[i].proces[k].cycle_left)
			{
				g_all.champ[i].proces[k].cycle_left--;
				if (!g_all.champ[i].proces[k].cycle_left)
				{
					arg = get_arguments(&g_all.champ[i].proces[k]);
					g_all.func[g_all.champ[i].proces[k].opcode - 1](&g_all.champ[i], &g_all.champ[i].proces[k], arg);
				}
			}
			else
			{
				g_all.champ[i].proces[k].opcode = read_arena_op(g_all.champ[i].proces[k].pc);
				if (!g_all.champ[i].proces[k].opcode)
				{
					g_all.champ[i].proces[k].pc = calc_pc(g_all.champ[i].proces[k].pc++);
					k--;
				}
				else
					g_all.champ[i].proces[k].cycle_left = get_cycle_left(g_all.champ[i].proces[k].opcode);
			}
		}
	}
	return (0);
}

int		beg_battle()
{
	int end;
	int i;
	int check;

	end = 0;
	i = -1;
	check = 0;
	ft_printf("begin battle\n");
	while (!end)
	{
		read_proces();
		g_all.ctd++;
		if (0)//!(g_all.cycle_to_die % g_all.ctd)) ----> condition a changer vraie au premier cycle !!
		{
			g_all.ctd = 0;
			if ((reset_proc() < NBR_LIVE) || (check == MAX_CHECKS))
			{
				g_all.cycle_to_die -= CYCLE_DELTA;
				check = 0;
				if (g_all.cycle_to_die <= 0 || !g_all.nb_proces_tot)
				{
					end = 1;
				}
			}
			check++;
		}
		print_debug_info();
		dump_memory();
		g_all.cycle++;
	}
	return (0);
}
