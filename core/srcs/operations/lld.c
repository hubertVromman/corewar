/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:58 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/29 19:20:15 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_lld(t_champ *champ, t_proces *proces, t_arg *args) // tester s'il prend 1  ou 4 bytes dans la memoire
{
	champ = NULL;

	if (args[1].type & T_IND)
		proces->reg[args[0].value] = args[1].value;
	else
		proces->reg[args[0].value] = read_byte(calc_pc(proces->pc + args[1].value), 4); // sinon changer ca
	proces->carry = proces->reg[args[0].value] == 0 ? 1 : 0;
	return (1);
}
