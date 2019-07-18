/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lecteur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:57:39 by sofchami          #+#    #+#             */
/*   Updated: 2019/07/18 20:03:58 by sofchami         ###   ########.fr       */
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
	t_proces *tmp;

	i = -1;
	total_lives = 0;
	while (++i < g_all.nb_champ)
	{
		tmp = g_all.champ[i].proces;
		while (tmp)
		{
			if (!tmp->lives_period)
				tmp->dead = 1;
			else
			{
				total_lives += tmp->lives_period;
				tmp->lives_period = 0;
			}
			tmp = tmp->next;
		}
	}
	return (total_lives);
}

int	 	read_proces()
{
	int i;
	int k;

	i = -1;
	while (i++ < g_all.nb_champ)
	{
		k = -1;
		while (++k < g_all.champ[i].nb_proces)
		{
			if (!g_all.champ[i].proces[k].cycle_left)
			{
				g_all.champ[i].proces[k].cycle_left--;
				if (!g_all.champ[i].proces[k].cycle_left)
				{
					pointeur_fonction[g_all.champ[i].proces[k].opcode];
				}
			}
			else
			{


				g_all.champ[i].proces[k].opcode = read_arena_op(g_all.champ[i].proces[k].pc);

			}


		}
	}
}

int		beg_battle()
{
	int end;
	int i;
	int check;

	end = 0;
	i = -1;
	check = 0;
	while (!end)
	{
		read_proces();
		//operations
		if (!(g_all.cycle_to_die % g_all.ctd))
		{
			g_all.ctd = 0;
			if ((reset_proc() < NBR_LIVE) || (check == MAX_CHECKS))
			{
				g_all.cycle_to_die -= CYCLE_DELTA;
				check = 0;
				if (g_all.cycle_to_die <= 0)
				{
					end = 1;
				}
			}
			check++;
		}
		g_all.ctd++;
		g_all.cycle++;
	}
	return (0);
}
