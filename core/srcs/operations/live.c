/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:53 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/11 00:44:33 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_live(t_champ *champ, t_proces *proces, t_arg *args)
{
	int i;

	i = -1;
	champ = NULL;
	while (++i < g_all.nb_champ)
	{
		if (g_all.champ[i].player_nb_arena == args[0].value)
		{
			g_all.champ[i].lives_period++;
			g_all.champ[i].last_live = g_all.cycle;
			g_all.player_last_live = i;
			if (!g_all.flags[VISU] && g_all.flags[INFORMATION])
				ft_printf("Player %d (%s) is said to be alive\n", g_all.champ[i].player_nb, g_all.champ[i].player_name);
		}
	}
	proces->lives_period++;
	return (1);
}
