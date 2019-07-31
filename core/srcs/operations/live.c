/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:53 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/31 01:29:44 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_live(t_champ *champ, t_proces *proces, t_arg *args)
{
	int i;
	// int id;

	i = args[0].size;
	// id = arg[0].value;
	// champ[id].lives_period++;
	// champ[id].last_live = g_all.cycle;
	// proces->lives_period++;
	// g_all.player_last_live = id;

	champ->lives_period++;
	champ->last_live = g_all.cycle;
	proces->lives_period++;
	// ft_printf("un processus dit que le joueur %d(%s) est en vie\n", champ->player_nb, champ->player_name);
	return (1);
}
