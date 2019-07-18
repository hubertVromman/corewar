/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:18 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/18 13:50:21 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
