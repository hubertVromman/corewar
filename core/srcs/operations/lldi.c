/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:02 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/11 06:22:02 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_lldi(t_champ *champ, t_proces *proces, t_arg *args)
{
	int ind_1;
	int ind_2;

	champ = NULL;
	if (args[0].type & T_REG)
		ind_1 = proces->reg[args[0].value];
	else
		ind_1 = args[0].value;
	if (args[1].type & T_REG)
		ind_2 = proces->reg[args[1].value];
	else
		ind_2 = args[1].value;
	proces->reg[args[2].value] =
		read_byte(calc_pc(proces->pc + (ind_1 + ind_2)), 4);
	proces->carry = proces->reg[args[0].value] == 0 ? 1 : 0;
	return (1);
}
