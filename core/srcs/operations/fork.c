/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:18 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/13 00:36:19 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_fork(t_champ *champ, t_proces *proces, t_arg *args)
{
	if (g_all.cycle == 1556)
		ft_printf("je rentre\n");
	create_proces(calc_pc(proces->pc + args[0].value % IDX_MOD), proces, champ);
	return (1);
}
