/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/28 21:12:33 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_ld(t_champ *champ, t_proces *proces, t_arg *args) // tester s'il prend 1  ou 4 bytes dans la memoire
{
	champ = NULL;

	if (args[1].type & T_IND)
		proces->reg[args[0].value] = args[1].value;
	else
		proces->reg[args[0].value] = read_byte(calc_pc(proces->pc + args[1].value % IDX_MOD), 4); // sinon changer ca
	proces->carry = proces->reg[args[0].value] == 0 ? 1 : 0;
	return (1);
}
