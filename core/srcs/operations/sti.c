/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:14 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/29 19:18:47 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_sti(t_champ *champ, t_proces *proces, t_arg *args)
{
	int		second_arg;
	int		third_arg;

	champ = NULL;
	if (args[1].type & T_REG)
		second_arg = proces->reg[args[1].value];
	else
		second_arg = args[1].value;
	if (args[2].type & T_REG)
		third_arg = proces->reg[args[2].value];
	else
		third_arg = args[2].value;
	write_int(proces, calc_pc(proces->pc + (second_arg + third_arg) % IDX_MOD), proces->reg[args[0].value]);
	return (1);
}
