/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lecteur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:57:39 by sofchami          #+#    #+#             */
/*   Updated: 2019/08/01 21:35:13 by sofchami         ###   ########.fr       */
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
	int total_lives_period;
	int k;

	i = -1;
	total_lives_period = 0;
	while (++i < g_all.nb_champ)
	{
		k = -1;
		while (++k < g_all.champ[i].nb_proces)
		{
			if (!g_all.champ[i].proces[k].lives_period)
			{
				detele_proces(&g_all.champ[i], k);
				k--;
			}
			else
			{
				total_lives_period += g_all.champ[i].proces[k].lives_period;
				g_all.champ[i].proces[k].lives_period = 0;
			}
		}
	}
	return (total_lives_period);
}

int		print_vm_info()
{
	int i;
	int k;
	int n;
	int x;
	int lives;

	i = -1;
	lives = 0;
	x = 250;
	while (++i < g_all.nb_champ)
		lives += g_all.champ[i].lives_period;
	jump_to(x, 0);
	ft_printf("%1$/30c Info %1$/30c\n", '-');
	i = 0;
	while (++i < 4)
	{
		jump_to(x, i);
		i == 1 ? ft_printf("Cycles = %4d", g_all.cycle) : 0;
		i == 2 ? ft_printf("Nbr de proces = %4d", g_all.nb_proces_tot) : 0;
		i == 3 ? ft_printf("Lives period = %4d", lives) : 0;
	}
	i++;
	n = -1;
	while (++n < g_all.nb_champ)
	{
		k = -1;
		while (++k < g_all.champ[n].nb_proces)
		{
			jump_to(x, i + k + (n ? g_all.champ[n - 1].nb_proces : 0));
			ft_printf("player_nb %2d | proces_id %2d | pc %4d | opcode " CHAR_HEX_PRINT " | cycle_left %4d\n", g_all.champ[n].player_nb, k, g_all.champ[n].proces[k].pc, g_all.champ[n].proces[k].opcode, g_all.champ[n].proces[k].cycle_left);
		}
	}
	if (g_all.max_proces <= g_all.nb_proces_tot)
		g_all.max_proces = g_all.nb_proces_tot;
	else
	{
		int tmp;
		tmp = g_all.nb_proces_tot + i;
		while (tmp < g_all.max_proces + i)
		{
			jump_to(x, tmp);
			ft_printf("%1$/80c", ' ');
			tmp++;
		}
	}
	return (0);
}

int		read_proces()
{
	int i;
	int k;
	t_arg *arg;

	i = g_all.nb_champ;
	while (i--)
	{
		print_vm_info();
		k = g_all.champ[i].nb_proces;
		while (k--)
		{
			if (g_all.champ[i].proces[k].cycle_left)
			{
				g_all.champ[i].proces[k].cycle_left--;
				if (!g_all.champ[i].proces[k].cycle_left)
				{
					arg = get_arguments(&g_all.champ[i].proces[k]);
					if (arg && (g_all.champ[i].proces[k].opcode > 0 && g_all.champ[i].proces[k].opcode < 16 ) && g_all.func[g_all.champ[i].proces[k].opcode - 1](&g_all.champ[i], &g_all.champ[i].proces[k], arg) != 0)
					{
						increment_pc(&g_all.champ[i].proces[k], g_all.champ[i].proces[k].opcode == ZJMP_OP ? 0 : arg[0].size + arg[1].size + arg[2].size + arg[3].size + g_op_tab[g_all.champ[i].proces[k].opcode - 1].codage + 1);
					}
					else
					{
						increment_pc(&g_all.champ[i].proces[k], 1);
					}
					g_all.champ[i].proces[k].opcode = read_arena_op(g_all.champ[i].proces[k].pc);
					g_all.champ[i].proces[k].cycle_left = get_cycle_left(g_all.champ[i].proces[k].opcode);
					// if (!g_all.flags[VISU])print_debug_info();
				}
			}
			else
			{
				g_all.champ[i].proces[k].opcode = read_arena_op(g_all.champ[i].proces[k].pc);
				g_all.champ[i].proces[k].cycle_left = get_cycle_left(g_all.champ[i].proces[k].opcode);
			}
		}
	}
	return (0);
}

int		update_cps()
{
	jump_to(0, 66);
	ft_printf("Cycles/second limit : %4d", g_all.visu.max_cps);
	return (0);
}

int		do_visu_stuff()
{
	int		i;
	int		sleep_time;
	int		current_cps;

	current_cps = g_all.visu.max_cps;
	update_cps();
	i = 0;
	sleep_time = 1000 / g_all.visu.max_cps;
	while (i < sleep_time)
	{
		i += 10;
		usleep(10 * 1000);
		if (current_cps != g_all.visu.max_cps)
		{
			update_cps();
			current_cps = g_all.visu.max_cps;
			i = 0;
		}
	}
	if (g_all.visu.pause)
	{
		return (1);
	}
	else
	{
		g_all.visu.skipped_frames = 0;
		return (0);
	}
}

int		beg_battle()
{
	int end;
	int i;
	int check;

	end = 1;
	i = -1;
	check = 0;
	// ft_printf("begin battle\n");
	while (end)
	{
		if (g_all.flags[VISU] && do_visu_stuff())
			continue;
		g_all.cycle++;
		read_proces();
		g_all.ctd++;
		if (g_all.ctd == g_all.cycle_to_die)
		{
			g_all.ctd = 0;
			if ((end = reset_proc()) >= NBR_LIVE || check == MAX_CHECKS)
			{
				g_all.cycle_to_die -= CYCLE_DELTA;
				check = 0;
				if (g_all.cycle_to_die <= 0 || g_all.nb_proces_tot == 0)
				{
					end = 0;
				}
			}
			check++;
		}
	}
	if (!g_all.flags[VISU])ft_printf("Contestant %d, \"%s\", has won !\n", g_all.champ[g_all.player_last_live].player_nb, g_all.champ[g_all.player_last_live].player_name);
	else while(1);
	return (0);
}
