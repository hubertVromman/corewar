/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lecteur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:57:39 by sofchami          #+#    #+#             */
/*   Updated: 2019/09/08 18:28:55 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			add_to_que(int player, int proces)
{
	if (!(g_all.queu = realloc(g_all.queu, sizeof(t_queu) *
		(g_all.len_queu + 1))))
		exit_func(MERROR, 0);
	g_all.queu[g_all.len_queu].player = player;
	g_all.queu[g_all.len_queu].proces = proces;
	g_all.len_queu++;
	return (0);
}

static int	do_actions(int i, int k)
{
	t_arg *arg;

	if ((arg = get_arguments(&g_all.champ[i].proces[k])))
	{
		g_all.func[g_all.champ[i].proces[k].opcode - 1](&g_all.champ[i],
			&g_all.champ[i].proces[k], arg);
		increment_pc(&g_all.champ[i].proces[k],
			g_all.champ[i].proces[k].opcode == ZJMP_OP ? 0 : g_all.arglen);
		add_to_que(i, k);
	}
	else
	{
		if (g_all.champ[i].proces[k].opcode > 0
			&& g_all.champ[i].proces[k].opcode < 17)
		{
			increment_pc(&g_all.champ[i].proces[k], g_all.arglen);
			add_to_que(i, k);
		}
		else
		{
			increment_pc(&g_all.champ[i].proces[k], 1);
			add_to_que(i, k);
		}
	}
	return (0);
}

static int	read_opcode(void)
{
	int player;
	int proces;

	player = g_all.queu[g_all.len_queu - 1].player;
	proces = g_all.queu[g_all.len_queu - 1].proces;
	if (g_all.len_queu)
	{
		g_all.champ[player].proces[proces].opcode =
			read_arena_op(g_all.champ[player].proces[proces].pc);
		g_all.champ[player].proces[proces].cycle_left =
			get_cycle_left(g_all.champ[player].proces[proces].opcode);
		g_all.len_queu--;
		return (g_all.len_queu ? read_opcode() : 0);
	}
	return (0);
}

static int	read_proces(void)
{
	int i;
	int k;

	i = g_all.nb_champ;
	while (i--)
	{
		k = g_all.champ[i].nb_proces;
		while (k--)
		{
			if (g_all.champ[i].proces[k].cycle_left > 1)
				g_all.champ[i].proces[k].cycle_left--;
			else
				do_actions(i, k);
		}
	}
	read_opcode();
	return (0);
}

int			single_cycle(void)
{
	g_all.cycle++;
	read_proces();
	g_all.ctd++;
	if (g_all.ctd == g_all.cycle_to_die)
	{
		g_all.ctd = 0;
		reset_proc();
		if (g_all.lives_period_tot >= NBR_LIVE || g_all.check == MAX_CHECKS)
		{
			g_all.cycle_to_die -= CYCLE_DELTA;
			g_all.check = 0;
			if (g_all.cycle_to_die <= 0 || g_all.nb_proces_tot == 0)
			{
				g_all.end = g_all.cycle;
			}
		}
		g_all.check++;
	}
	return (0);
}

int			beg_battle(void)
{
	g_all.visu.nb_frames_to_skip = 10;
	while (1)
	{
		if (g_all.flags[VISU])
			do_visu_stuff();
		else
		{
			single_cycle();
			if (g_all.dump_period && g_all.cycle == g_all.dump_period)
			{
				dump_memory();
				exit_func(0, 0);
			}
			if (g_all.end)
			{
				ft_printf("Contestant %d, %s, has won !\n",
					g_all.champ[g_all.player_last_live].index_player + 1,
					g_all.champ[g_all.player_last_live].player_name);
				break ;
			}
		}
	}
	return (0);
}
