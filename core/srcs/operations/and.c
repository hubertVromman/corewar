/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:12 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/19 13:39:30 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_add(t_champ *champ, t_proces *proces, t_arg *args)
{
	champ = NULL;
	if (args[0].value > REG_NUMBER || args[0].value < 1 || args[1].value >
		REG_NUMBER || args[1].value < 1 || args[2].value > REG_NUMBER ||
		args[2].value < 1)
	{
		proces->carry = 0;
		return (-1);
	}
	else
	{
		proces->reg[args[2].value] = proces->reg[args[0].value] & proces->reg[args[1].value];
		proces->carry = proces->reg[args[2].value] == 0 ? 1 : 0;
		return (0);
	}
}
