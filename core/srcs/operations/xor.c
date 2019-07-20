/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:22 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/19 13:39:05 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_xor(t_champ *champ, t_proces *proces, t_arg *args)
{
	int		first_arg;
	int		second_arg;

	champ = NULL;
	if (args[0].type & T_IND)
		first_arg = g_all.arena[calc_pc(proces->pc + args[0].value % IDX_MOD)]; // a tester
	else if (args[0].type & T_DIR)
		first_arg = args[0].value; // a tester
	else if (args[0].value > REG_NUMBER || args[0].value < 1)
	{
		proces->carry = 0;
		return (-1);
	}
	else
		first_arg = proces->reg[args[0].value - 1];
	if (args[1].type & T_IND)
		second_arg = g_all.arena[calc_pc(proces->pc + args[1].value % IDX_MOD)]; // a tester
	else if (args[1].type & T_DIR)
		second_arg = args[1].value; // a tester
	else if (args[1].value > REG_NUMBER || args[1].value < 1)
	{
		proces->carry = 0;
		return (-1);
	}
	else
		second_arg = proces->reg[args[1].value - 1];
	if (args[2].value > REG_NUMBER || args[2].value < 1)
	{
		proces->carry = 0;
		return (-1);
	}
	proces->reg[args[2].value - 1] = first_arg ^ second_arg; // a tester pour erreur de cast (0xfffffef0)
	proces->carry = proces->reg[args[2].value - 1] == 0 ? 1 : 0;
	return (0);
}
