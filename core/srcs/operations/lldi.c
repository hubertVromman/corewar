/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:02 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/29 19:20:27 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_lldi(t_champ *champ, t_proces *proces, t_arg *args)
{
	champ = NULL;
	int ind_1;
	int ind_2;

	champ = NULL;

	if (args[0].type & T_REG)
	{
		if (args[0].value > REG_NUMBER || args[0].value < 0)
		return (-1);
		ind_1 = proces->reg[args[0].value - 1];
	}
	else
		ind_1 = args[0].value;
	if (args[1].type & T_REG)
	{
		if (args[1].value > REG_NUMBER || args[1].value < 0)
		return (-1);
		ind_2 = proces->reg[args[1].value - 1];
	}
	else
		ind_2 = args[1].value;
	proces->reg[args[2].value - 1] = read_byte(calc_pc(proces->pc + (ind_1 + ind_2)), 4);
	proces->carry = proces->reg[args[0].value - 1] == 0 ? 1 : 0;
	return (1);
}
