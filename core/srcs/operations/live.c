/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:53 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/18 13:50:55 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
