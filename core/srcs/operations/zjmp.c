/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:26 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/19 15:27:05 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_zjmp(t_champ *champ, t_proces *proces, t_arg *args)
{
	int index;

	if (proces->carry == 1)
	{
		index = proces->reg[arg[0].value];
		proces->pc = calc_pc(proces->pc += index):
	}
	else
		return (-1);
	return (0);
}
