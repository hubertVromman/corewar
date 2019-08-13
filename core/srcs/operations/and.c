/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:12 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/13 00:35:19 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_and(t_champ *champ, t_proces *proces, t_arg *args)
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
	proces->reg[args[2].value] = (short)(first_arg & second_arg); // a tester pour erreur de cast (0xfffffef0)
	// if (g_all.cycle < 1538)
	// {
	// 	ft_printf("reg %d   %d  %d - id = %d | cycle = %d\n", args[2].value, first_arg, second_arg, proces->id_proces, g_all.cycle);
	// 	ft_printf("%d\n", proces->reg[args[2].value]);
	// }
	proces->carry = proces->reg[args[2].value] == 0 ? 1 : 0;
	return (1);
}
