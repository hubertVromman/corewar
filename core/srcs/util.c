/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:16:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/01 20:21:19 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_cycle_left(int opcode)
{
	ft_printf("=== opcode %d\n", opcode);
	if (opcode < 1 || opcode > 16)
	{
		ft_printf("ici\n");
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
	proc->carry = 0;
	proc->cycle_left = 0;
	proc->opcode = 0;
	proc->id_proces = g_all.id_proces;
	if (parent)
	{
		ft_memcpy(proc->reg, parent->reg, REG_NUMBER * 4);
	}
	else
	{
		proc->reg[0] = champ->player_nb;
	}
	proc->champ = champ;
	champ->nb_proces++;
	g_all.nb_proces_tot++;
	g_all.id_proces++;
	increment_pc(proc, 0);
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

int		dump_memory_colored() // protection et utile que debut de game
{
	int		i;
	int		j;
	int		c;

	char *s = malloc(MEM_SIZE * 3 + g_all.nb_champ * 9);
	char *buffer;
	i = -1;
	j = 0;
	while (++i < MEM_SIZE)
	{
		c = -1;
		while (++c < g_all.nb_champ)
		{
			if (i == g_all.champ[c].proces->pc)
			{
				ft_printf(COLOR_PRINT "%#>", g_all.champ[c].color_id, &buffer);
				memcpy(s + i * 3 + j, buffer, 5);
				j += 5;
			}
		}
		ft_printf(CHAR_HEX_PRINT "%c%#>", g_all.arena[i], (i + 1) % 64 ? ' ' : '\n', &buffer);
		memcpy(s + i * 3 + j, buffer, 3);
		c = -1;
		while (++c < g_all.nb_champ)
		{
			if (i == g_all.champ[c].proces->pc + g_all.champ[c].exec_size - 1)
			{
				memcpy(s + (i + 1) * 3 + j, NC, 4);
				j += 4;
			}
		}
	}
	write(1, s, MEM_SIZE * 3 + g_all.nb_champ * 9);
	return (0);
}
