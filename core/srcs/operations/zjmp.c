/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:26 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/24 01:08:35 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_zjmp(t_champ *champ, t_proces *proces, t_arg *args)
{
	champ = NULL;

	if (proces->carry == 1)
	{
		proces->pc = calc_pc(proces->pc + args[0].value);
	}
	else
		return (-1);
	return (0);
}
