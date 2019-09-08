/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:22 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/11 06:21:33 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_xor(t_champ *champ, t_proces *proces, t_arg *args)
{
	int		first_arg;
	int		second_arg;

	champ = NULL;
	if (args[0].type & T_IND || args[0].type & T_DIR)
		first_arg = args[0].value;
	else
		first_arg = proces->reg[args[0].value];
	if (args[1].type & T_IND || args[1].type & T_DIR)
		second_arg = args[1].value;
	else
		second_arg = proces->reg[args[1].value];
	proces->reg[args[2].value] = first_arg ^ second_arg;
	proces->carry = proces->reg[args[2].value] == 0 ? 1 : 0;
	return (1);
}
