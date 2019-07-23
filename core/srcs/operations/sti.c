/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:14 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/24 00:39:40 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_sti(t_champ *champ, t_proces *proces, t_arg *args)
{
	int		second_arg;
	int		third_arg;

	champ = NULL;
	if (args[0].value > REG_NUMBER || args[0].value < 1)
		return (-1);
	if (args[1].type & T_REG)
	{
		if (args[1].value > REG_NUMBER || args[1].value < 1)
			return (-1);
		second_arg = proces->reg[args[1].value - 1];
	}
	else
		second_arg = args[1].value;
	if (args[2].type & T_REG)
	{
		if (args[2].value > REG_NUMBER || args[2].value < 1)
			return (-1);
		third_arg = proces->reg[args[2].value - 1];
	}
	else
		third_arg = args[2].value;
	write_int(proces, calc_pc(proces->pc + second_arg + third_arg % IDX_MOD), proces->reg[args[0].value - 1]);
	return (0);
}
