/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:16:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/08 05:00:12 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_cycle_left(int opcode)
{
	if (opcode < 1 || opcode > 16)
	{
		return (1);
	}
	else
		return (g_op_tab[opcode - 1].cycle_op);
}

int		sort_proces(t_champ *champ)
{
	t_proces tmp;
	int		i;

	i = -1;
	while (++i < champ->nb_proces)
	{
		if (i + 1 < champ->nb_proces && champ->proces[i].id_proces > champ->proces[i + 1].id_proces)
		{
			tmp = champ->proces[i];
			champ->proces[i] = champ->proces[i + 1];
			champ->proces[i + 1] = tmp;
			i = -1;
		}
	}
	return (0);
}

int		play_sound(int i)
{
	system("pkill afplay &");
	if (i == 1)
	system("afplay sound/Ta_da.mp3 &");
	if (i == 2)
	system("afplay sound/power_off.mp3 &");
	return (0);
}

int		detele_proces(t_champ *champ, int id_proces)
{
	if (g_all.flags[VISU])
	{
		jump_to_mem(champ->proces[id_proces].pc);
		ft_printf(CHAR_HEX_PRINT, g_all.arena[champ->proces[id_proces].pc]);
	}
	ft_memcpy(&(champ->proces[id_proces]), &(champ->proces[champ->nb_proces - 1]), sizeof(t_proces));
	champ->nb_proces--;
	g_all.nb_proces_tot--;
	sort_proces(champ);
	// play_sound(2);
	return (0);
}

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
	proc->carry = 0;
	proc->id_proces = g_all.id_proces;
	if (parent)
		ft_memcpy(proc->reg, parent->reg, REG_NUMBER * 4);
	else
		proc->reg[0] = champ->player_nb;
	proc->champ = champ;
	proc->color_rgb = proc->champ->color_rgb + champ->nb_proces * COLOR_INCREMENT * 5;
	if (champ->nb_proces)
		increment_pc(proc, 0);
	champ->nb_proces++;
	g_all.nb_proces_tot++;
	g_all.id_proces++;
	// g_all.cycle ? play_sound(2) :0;
	return(0);
}

int		dump_memory()
{
	int		i;
	char *buffer;

	char *s = malloc(MEM_SIZE * 3);
	i = -1;
	while (++i < MEM_SIZE)
	{
		ft_printf(CHAR_HEX_PRINT "%c%#>", g_all.arena[i], (i + 1) % 64 ? ' ' : '\n', &buffer);
		memcpy(s + i * 3, buffer, 3);
	}
	write(1, s, MEM_SIZE * 3);
	return (0);
}

int		dump_memory_colored() // manque protection et utile que debut de game
{
	int		i;
	int		p;
	int		l;

	i = -1;
	p = 0;
	l = HEADER_HEIGHT;
	ft_printf("<b>");
	jump_to(2, HEADER_HEIGHT);
	while (++i < MEM_SIZE)
	{
		if (i >= g_all.champ[p].proces->pc && i < (g_all.champ[p].proces->pc + g_all.champ[p].exec_size))
			ft_printf(RGB_PRINT "%.2hhx", (g_all.champ[p].color_rgb >> 16) & 0xff, (g_all.champ[p].color_rgb >> 8) & 0xff, (g_all.champ[p].color_rgb >> 0) & 0xff, g_all.arena[i]);
		else
			ft_printf(RGB_PRINT "%.2hhx", 0x80, 0x80, 0x80, g_all.arena[i]);
		if (!((i + 1) % 64) && ++l)
			jump_to(2, l);
		else
			ft_printf(" ");
		if (p < (g_all.nb_champ - 1) && i + 1 == g_all.champ[p + 1].proces->pc)
			p++;
	}
	return (0);
}
