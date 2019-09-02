/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lecteur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:57:39 by sofchami          #+#    #+#             */
/*   Updated: 2019/09/02 19:08:11 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int 	add_to_que(t_proces *proces, int player)
{
	g_all.id_queu[g_all.len_queu] = proces->id_proces;
	g_all.player_queu[g_all.len_queu] = player;
	g_all.len_queu++;
	return (0);
}

int		do_actions(int i, int k)
{
	t_arg *arg;

	arg = get_arguments(&g_all.champ[i].proces[k]);
	if (arg && (g_all.champ[i].proces[k].opcode > 0 && g_all.champ[i].proces[k].opcode < 17 ) && g_all.func[g_all.champ[i].proces[k].opcode - 1](&g_all.champ[i], &g_all.champ[i].proces[k], arg) != 0)
	{
		// if (g_all.cycle > 3500 && i == 0 && g_all.cycle < 4500)
		// 	ft_printf("1) %d  | %d -> %s    pc = %d\n", g_all.cycle, g_all.champ[i].proces[k].id_proces, g_op_tab[g_all.champ[i].proces[k].opcode - 1].name, g_all.champ[i].proces[k].pc);
		increment_pc(&g_all.champ[i].proces[k], g_all.champ[i].proces[k].opcode == ZJMP_OP ? 0 : arg[0].size + arg[1].size + arg[2].size + arg[3].size + g_op_tab[g_all.champ[i].proces[k].opcode - 1].codage + 1);
		add_to_que(g_all.champ[i].proces + k, i);
	}
	else
	{
		if (g_all.champ[i].proces[k].opcode > 0 && g_all.champ[i].proces[k].opcode < 17) // soucis dans se if !!!!!
		{
			/*
			**---> Gagnant 4x contre Gagnant
			**-- cycle 3605   id 36 saut de 2;
			**-- cycle 3674   id 6 saut de 2;
			**---> Gagnant contre jumper et bizgork
			**-- saut de 2 et de 4 whuuut :P
			*/
			increment_pc(&g_all.champ[i].proces[k], g_op_tab[g_all.champ[i].proces[k].opcode - 1].nb_params + 2);
			// increment_pc(&g_all.champ[i].proces[k], 2);
			add_to_que(g_all.champ[i].proces + k, i);
		}
		else
		{
			// if (g_all.cycle > 3500 && i == 1 && g_all.cycle < 4500)
				// ft_printf("3) %d  | %d -> %s    pc = %d\n", g_all.cycle, g_all.champ[i].proces[k].id_proces, "-NVA-", g_all.champ[i].proces[k].pc);
			increment_pc(&g_all.champ[i].proces[k], g_all.arglen + 1);
			add_to_que(g_all.champ[i].proces + k, i);
		}
	}
	return (0);
}

int		read_opcode()
{
	int i;
	int player;

	i = -1;
	player = g_all.player_queu[g_all.len_queu - 1];
	if (g_all.len_queu)
	{
		while (++i < g_all.champ[player].nb_proces)
		{
			if (g_all.champ[player].proces[i].id_proces == g_all.id_queu[g_all.len_queu - 1])
			{
				g_all.champ[player].proces[i].opcode = read_arena_op(g_all.champ[player].proces[i].pc);
				g_all.champ[player].proces[i].cycle_left = get_cycle_left(g_all.champ[player].proces[i].opcode);
				g_all.len_queu--;
				return (g_all.len_queu ? read_opcode() : 0);
			}
		}
	}
	return (0);
}

int		read_proces()
{
	int i;
	int k;

	g_all.id_queu = ft_memalloc(sizeof(int) * g_all.nb_proces_tot * 2);
	g_all.player_queu = ft_memalloc(sizeof(int) * g_all.nb_proces_tot * 2);
	i = g_all.nb_champ;
	while (i--)
	{
		k = g_all.champ[i].nb_proces;
		while (k--)
		{
			if (g_all.champ[i].proces[k].cycle_left)
			{
				g_all.champ[i].proces[k].cycle_left--;
				if (!g_all.champ[i].proces[k].cycle_left)
				{
					do_actions(i, k);
				}
			}
		}
	}
	read_opcode();
	free(g_all.id_queu);
	free(g_all.player_queu);
	return (0);
}

static int		do_visu_stuff()
{
	int			has_frame;

	has_frame = 1;
	update_cps();
	if (!g_all.end)
		pthread_create(&g_all.visu.thread_calcul, NULL, th_calcul, NULL);
	else if (!g_all.visu.pause)
	{
		pthread_create(&g_all.visu.thread_calcul, NULL, th_calcul, NULL);
		if (g_all.visu.flame)
			pthread_create(&g_all.visu.thread_flamme, NULL, th_feu, NULL);
	}
	else if (!g_all.cycle)
		print_vm_info();
	else
		has_frame = 0;
	usleep(1000 * 1000 / g_all.visu.max_cps);
	pthread_join(g_all.visu.thread_calcul, NULL);
	pthread_join(g_all.visu.thread_flamme, NULL);
	update_cps();
	if (has_frame)
		print_frame_diff();
	if (g_all.visu.flame)
	{
		if (!g_all.visu.thread_sound)
			pthread_create(&g_all.visu.thread_sound, NULL, sound_feu, NULL);
	}
	return (0);
}

int		beg_battle()
{
	g_all.visu.nb_frames_to_skip = 10;
	g_all.end = 1;
	while (1)
	{
		if (g_all.flags[VISU])
			do_visu_stuff();
		else
		{
			g_all.cycle++;
			read_proces();
			g_all.ctd++;
			if (g_all.ctd == g_all.cycle_to_die)
			{
				g_all.ctd = 0;
				if ((g_all.end = reset_proc()) >= NBR_LIVE || g_all.check == MAX_CHECKS)
				{
					g_all.cycle_to_die -= CYCLE_DELTA;
					g_all.check = 0;
					if (g_all.cycle_to_die <= 0 || g_all.nb_proces_tot == 0)
					{
						g_all.end = 0;
					}
				}
				g_all.check++;
			}
			if (g_all.dump_period && g_all.cycle == g_all.dump_period)
			{
				dump_memory();
				exit_func(0, 0);
			}
			if (!g_all.end)
			{
				ft_printf("Contestant %d, %s, has won !", g_all.champ[g_all.player_last_live].index_player + 1, g_all.champ[g_all.player_last_live].player_name);
				break;
			}
		}
	}
	return (0);
}
