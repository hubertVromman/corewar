/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:26 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/18 21:00:03 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
