/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:06 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/29 19:20:42 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_or(t_champ *champ, t_proces *proces, t_arg *args)
{
	int		first_arg;
	int		second_arg;

	champ = NULL;

	if (args[0].type & T_IND || args[0].type & T_DIR)
		first_arg = args[0].value; // a tester
	else
		first_arg = proces->reg[args[0].value];
	if (args[1].type & T_IND || args[1].type & T_DIR)
		second_arg = args[1].value; // a tester
	else
		second_arg = proces->reg[args[1].value];
	proces->reg[args[2].value] = (short)(first_arg | second_arg); // a tester pour erreur de cast (0xfffffef0)
	proces->carry = proces->reg[args[2].value] == 0 ? 1 : 0;
	return (1);
}
