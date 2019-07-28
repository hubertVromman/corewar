/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:55:29 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/28 21:13:01 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_ldi(t_champ *champ, t_proces *proces, t_arg *args)
{
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
	proces->reg[args[2].value - 1] = read_byte(calc_pc(proces->pc + (ind_1 + ind_2) % IDX_MOD), 4);
	return (1);
}
