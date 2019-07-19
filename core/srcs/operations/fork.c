/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:18 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/19 15:26:14 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_fork(t_champ *champ, t_proces *proces, t_arg *args)
{
	int		pc;
	int		param;

	pc = proces->pc;
	param = proces->reg[arg[0]->value];
	create_proces(calc_pc(pc + (param % IDX_MOD)), proces, champ);
	return (0);
}
