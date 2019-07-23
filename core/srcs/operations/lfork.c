/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:48 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/24 00:39:08 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_lfork(t_champ *champ, t_proces *proces, t_arg *args)
{
	int		pc;

	pc = proces->pc;
	create_proces(calc_pc(pc + args[0].value), proces, champ);
	return (0);
}
