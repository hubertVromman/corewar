/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lecteur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:57:39 by sofchami          #+#    #+#             */
/*   Updated: 2019/08/27 23:13:26 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		do_actions(int i, int k)
{
	int l;
	t_arg *arg;

	l = 0;
	arg = get_arguments(&g_all.champ[i].proces[k]);
	if (arg && (g_all.champ[i].proces[k].opcode > 0 && g_all.champ[i].proces[k].opcode < 17 ) && g_all.func[g_all.champ[i].proces[k].opcode - 1](&g_all.champ[i], &g_all.champ[i].proces[k], arg) != 0)
	{
		increment_pc(&g_all.champ[i].proces[k], g_all.champ[i].proces[k].opcode == ZJMP_OP ? 0 : arg[0].size + arg[1].size + arg[2].size + arg[3].size + g_op_tab[g_all.champ[i].proces[k].opcode - 1].codage + 1);
		g_all.queu[l] = &g_all.champ[i].proces[k];
		l++;
	}
	else
	{
		if (g_all.champ[i].proces[k].opcode > 1 && g_all.champ[i].proces[k].opcode < 16)
			increment_pc(&g_all.champ[i].proces[k], g_op_tab[g_all.champ[i].proces[k].opcode - 1].nb_params + 2);
		else
			increment_pc(&g_all.champ[i].proces[k], 1);
	}
	return (l);
}

int		read_opcode(int l)
{
	int i;

	i = -1;
	while (++i < l)
	{
		g_all.queu[i]->opcode = read_arena_op(g_all.queu[i]->pc);
		g_all.queu[i]->cycle_left = get_cycle_left(g_all.queu[i]->opcode);
	}
	return (0);
}

int		read_proces()
{
	int i;
	int k;
	int		l;

	ft_bzero(&g_all.queu, sizeof(g_all.queu));
	i = g_all.nb_champ;
	l = 0;
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
					l = do_actions(i, k);
				}
			}
			else // utilité de ce else ? normalement il devrait pas rentrer dedans...
			{
				g_all.champ[i].proces[k].opcode = read_arena_op(g_all.champ[i].proces[k].pc);
				g_all.champ[i].proces[k].cycle_left = get_cycle_left(g_all.champ[i].proces[k].opcode);
			}
		}
	}
	read_opcode(l);
	return (0);
}

int		do_visu_stuff()
{
	int			i;
	int			sleep_time;
	static int	current_cps = 0;
	int			has_frame;
	char		*tmp;

	i = 0;
	has_frame = 0;
	tmp = NULL;
	if (!g_all.visu.pause)
	{
		if (g_all.has_been_paused)
		{
			jump_to(5, 5);
			ft_printf(RESET_COLOR "Running");
			g_all.has_been_paused = 0;
		}
		has_frame = 1;
		pthread_create(&g_all.visu.thread_calcul, NULL, th_calcul, NULL);
		if (g_all.visu.flame)
			pthread_create(&g_all.visu.thread_flamme, NULL, th_feu, NULL);
	}
	else
	{
		add_string_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * 5) + 5, "Pause  ", 0xffffff, 0);
		jump_to(5, 5);
		ft_printf(RESET_COLOR "Pause  ");
		system("pkill afplay");
		g_all.has_been_paused = 1;
	}
	sleep_time = 1000 / g_all.visu.max_cps;
	while (i < sleep_time)
	{
		i += 10;
		if (current_cps != g_all.visu.max_cps)
		{
			update_cps();
			current_cps = g_all.visu.max_cps;
			sleep_time = 1000 / g_all.visu.max_cps;
			i = 0;
		}
		usleep(10 * 1000);
	}
	pthread_join(g_all.visu.thread_calcul, NULL);
	pthread_join(g_all.visu.thread_flamme, NULL);
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
	while (g_all.end)
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
		}
	}
	if (!g_all.flags[VISU])ft_printf("Contestant %d, \"%s\", has won !\n", g_all.champ[g_all.player_last_live].player_nb, g_all.champ[g_all.player_last_live].player_name);
	else {ft_printf("fin\n");while(1);}
	return (0);
}
