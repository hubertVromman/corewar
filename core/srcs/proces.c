/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:33:01 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/28 01:33:03 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		create_proces(int pc, t_proces *parent, t_champ *champ)
{
	t_proces *proc;

	if (!(champ->proces = realloc(champ->proces, sizeof(t_proces) * (champ->nb_proces + 1))))
		return (-1);
	proc = &(champ->proces[champ->nb_proces]);
	ft_bzero(proc, sizeof(t_proces));
	proc->pc = pc;
	proc->opcode = read_arena_op(proc->pc);
	proc->cycle_left = get_cycle_left(proc->opcode);
	proc->id_proces = g_all.id_proces;
	if (parent)
	{
		ft_memcpy(proc->reg, parent->reg, REG_NUMBER * 4);
		proc->carry = parent->carry;
	}
	else
		proc->reg[0] = champ->player_nb_arena;
	proc->champ = champ;
	proc->color_rgb = proc->champ->color_rgb + champ->nb_proces * COLOR_INCREMENT;
	if (champ->nb_proces)
		increment_pc(proc, 0);
	champ->nb_proces++;
	g_all.nb_proces_tot++;
	g_all.id_proces++;
	g_all.cycle ? play_sound(S_LIVE) :0;
	return(0);
}

int		delete_proces(t_champ *champ, int id_proces)
{
	int		pos;
	char	*buf;

	if (g_all.flags[VISU])
	{
		buf = NULL;
		pos = jump_to_buf(champ->proces[id_proces].pc);
		ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[champ->proces[id_proces].pc], &buf);
		write_to_buf(g_all.visu.next_frame + pos, buf[0], g_all.color[champ->proces[id_proces].pc], 0);
		write_to_buf(g_all.visu.next_frame + pos + 1, buf[1], g_all.color[champ->proces[id_proces].pc], 0);
		free(buf);
	}
	// play_sound(S_DEATH);
	return (0);
}

int		reset_proc()
{
	int		i;
	int		total_lives_period;
	int		k;
	int		deleted;

	i = -1;
	total_lives_period = 0;
	while (++i < g_all.nb_champ)
	{
		deleted = 0;
		k = -1;
		while (++k < g_all.champ[i].nb_proces)
		{
			if (!g_all.champ[i].proces[k].lives_period)
			{
				delete_proces(&(g_all.champ[i]), k);
				deleted++;
			}
			else
			{
				total_lives_period += g_all.champ[i].proces[k].lives_period;
				g_all.champ[i].proces[k].lives_period = 0;
				ft_memcpy(&(g_all.champ[i].proces[k - deleted]), &(g_all.champ[i].proces[k]), sizeof(t_proces));
			}
		}
		g_all.champ[i].lives_period = 0;
		g_all.champ[i].nb_proces -= deleted;
		g_all.nb_proces_tot -= deleted;
	}

	return (total_lives_period);
}
