/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 20:57:41 by sofchami          #+#    #+#             */
/*   Updated: 2019/07/18 02:16:59 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		calc_pc(int pc)
{
	if (pc > MEM_SIZE)
		pc %= MEM_SIZE;
	return (pc);
}

int		operation_fork(int champ, int id_proces)
{
	int		pc_pere;
	t_champ *tmp;

	tmp = g_all.champ[champ];
	while (tmp.proces)
	{
		if (tmp.proces->id_proces == id_proces)
			pc_pere = tmp.proces->pc;
		if (!tmp.proces->next && pc_pere)
		{
			tmp.proces->next = init_proces(calc_pc(pc_pere + (pc_pere % IDX_MOD)));
			champ->num_proces++;
			tmp.proces->next->id_proces = champ->num_proces;
			break ;
		}
		tmp.proces = tmp.proces->next;
	}
	return (0);
}

int		operation_lfork(int champ, int id_proces)
{
	int		pc_pere;
	t_champ *tmp;

	tmp = g_all.champ[champ];
	while (tmp.proces)
	{
		if (tmp.proces->id_proces == id_proces)
			pc_pere = tmp.proces->pc;
		if (!tmp.proces->next && pc_pere)
		{
			tmp.proces->next = init_proces(calc_pc(pc_pere * 2));
			champ->num_proces++;
			tmp.proces->next->id_proces = champ->num_proces;
			break ;
		}
		tmp.proces = tmp.proces->next;
	}
	return (0);
}

int		operation_live(int champ, int id_proces)
{
	int		i;
	t_champ *tmp;

	tmp = g_all.champ[champ];
	while (tmp.proces)
	{
		if (tmp.proces->id_proces == id_proces)
		{
			champ->lives_period++;
			champ->last_live = g_all.cycle;
			tmp.proces->lives_period++;
			break ;
		}
		tmp.proces = tmp.proces->next;
	}
	return (0);
}

int		operation_zjmp(int champ, int id_proces, int index)
{
	t_champ *tmp;

	tmp = g_all.champ[champ];
	while (tmp.proces)
	{
		if (tmp.proces->id_proces == id_proces)
		{
			tmp.proces->pc %= (tmp.proces->pc + index);
			break ;
		}
		tmp.proces = tmp.proces->next;
	}
	return (0);
}
