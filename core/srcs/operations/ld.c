/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/24 00:38:58 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_ld(t_champ *champ, t_proces *proces, t_arg *args) // tester s'il prend 1  ou 4 bytes dans la memoire
{
	champ = NULL;

	if (args[0].value > REG_NUMBER || args[0].value < 1)
		return (-1);
	if (args[1].type & T_IND)
		proces->reg[args[0].value - 1] = args[1].value;
	else
		proces->reg[args[0].value - 1] = g_all.arena[calc_pc(proces->pc + args[1].value % IDX_MOD)]; // sinon changer ca
	proces->carry = proces->reg[args[0].value - 1] == 0 ? 1 : 0;
	return (0);
}
