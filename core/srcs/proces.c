/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:33:01 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/10 05:50:19 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	init_proces_var(t_proces *new, t_proces *parent, t_champ *champ)
{
	new->id_proces = g_all.id_proces++;
	if (parent)
	{
		ft_memcpy(new->reg, parent->reg, sizeof(int) * REG_NUMBER);
		new->carry = parent->carry;
		new->lives_period = parent->lives_period;
		add_to_que(champ->index_player, champ->nb_proces);
	}
	else
	{
		new->opcode = read_arena_op(new->pc);
		new->cycle_left = get_cycle_left(new->opcode);
		new->reg[0] = champ->player_nb_arena;
	}
	g_all.process_tracker[g_all.tracker_size].player = champ->index_player;
	g_all.process_tracker[g_all.tracker_size].proces = champ->nb_proces;
	new->color_rgb = champ->color_rgb + champ->nb_proces * COLOR_INCREMENT;
	return (0);
}

int			create_proces(int pc, t_proces *parent, t_champ *champ)
{
	t_proces *new;
	long int tmp;

	tmp = parent - champ->proces;
	if (!(champ->proces = realloc(champ->proces, sizeof(t_proces) *
		(champ->nb_proces + 1))))
		exit_func(MERROR, 0);
	if (!(g_all.process_tracker = realloc(g_all.process_tracker, sizeof(t_pp) *
		(g_all.tracker_size + 1))))
		exit_func(MERROR, 0);
	if (parent)
		parent = champ->proces + tmp;
	new = &(champ->proces[champ->nb_proces]);
	ft_bzero(new, sizeof(t_proces));
	new->pc = pc;
	init_proces_var(new, parent, champ);
	if (champ->nb_proces)
		increment_pc(new, 0);
	champ->nb_proces++;
	g_all.nb_proces_tot++;
	g_all.tracker_size++;
	if (g_all.flags[VISU] && g_all.cycle && !g_all.flags[SILENCE])
		play_sound(S_LIVE);
	return (0);
}

static int	delete_proces(t_champ *champ, int id_proces)
{
	int		pos;

	if (g_all.flags[VISU])
	{
		pos = jump_to_buf(champ->proces[id_proces].pc);
		if (ft_printf(CHAR_HEX_PRINT "%#>",
			g_all.arena[champ->proces[id_proces].pc], &g_all.buf) < 0)
			exit_func(MERROR, 0);
		write_to_buf(g_all.visu.next_frame + pos, g_all.buf[0],
			g_all.color[champ->proces[id_proces].pc], 0);
		write_to_buf(g_all.visu.next_frame + pos + 1, g_all.buf[1],
			g_all.color[champ->proces[id_proces].pc], 0);
		free(g_all.buf);
	}
	if (g_all.flags[VISU] && !g_all.flags[SILENCE])
		play_sound(S_DEATH);
	g_all.process_tracker[champ->proces[id_proces].id_proces].player = -1;
	return (0);
}

static int	check_dead_proces(int champ_idx, int proces_idx, int deleted)
{
	if (!g_all.champ[champ_idx].proces[proces_idx].lives_period)
	{
		delete_proces(&(g_all.champ[champ_idx]), proces_idx);
		deleted++;
	}
	else
	{
		g_all.champ[champ_idx].proces[proces_idx].lives_period = 0;
		g_all.process_tracker[g_all.champ[champ_idx]
			.proces[proces_idx].id_proces].proces -= deleted;
		ft_memcpy(&(g_all.champ[champ_idx].proces[proces_idx - deleted]),
			&(g_all.champ[champ_idx].proces[proces_idx]), sizeof(t_proces));
	}
	return (deleted);
}

int			reset_proc(void)
{
	int		i;
	int		j;
	int		deleted;

	i = -1;
	while (++i < g_all.nb_champ)
	{
		deleted = 0;
		j = -1;
		while (++j < g_all.champ[i].nb_proces)
		{
			deleted = check_dead_proces(i, j, deleted);
		}
		g_all.champ[i].lives_period = 0;
		g_all.champ[i].nb_proces -= deleted;
		g_all.nb_proces_tot -= deleted;
	}
	if (g_all.lives_period_tot == 0)
	{
		g_all.end = g_all.cycle;
	}
	return (0);
}
