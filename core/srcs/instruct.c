/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 20:57:41 by sofchami          #+#    #+#             */
/*   Updated: 2019/07/13 21:16:23 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		calc_pc(int pc)
{
	if (pc > MEM_SIZE)
		pc %= MEM_SIZE;
	return (0);
}

int		operation_fork(t_champ *champ, int id_proces)
{
	int		pc_pere;
	t_champ tmp;

	tmp = *champ;
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

int		operation_lfork(t_champ *champ, int id_proces)
{
	int		pc_pere;
	t_champ tmp;

	tmp = *champ;
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
