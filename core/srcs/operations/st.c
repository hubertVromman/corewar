/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:10 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/13 04:20:35 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_st(t_champ *champ, t_proces *proces, t_arg *args)
{
	champ = NULL;
	if (args[1].type & T_REG)
		proces->reg[args[1].value] = proces->reg[args[0].value];
	else
	{
		write_int(proces, calc_pc(proces->pc + args[1].value % IDX_MOD),
			proces->reg[args[0].value]);
	}
	return (1);
}
