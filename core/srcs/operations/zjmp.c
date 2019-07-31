/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:26 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/31 23:05:16 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_zjmp(t_champ *champ, t_proces *proces, t_arg *args)
{
	champ = NULL;

	if (proces->carry == 0)
	{
		increment_pc(proces, args[0].value);
	}
	else   // Pas sur si faut enlever se else, "a tester"
	{
		increment_pc(proces, 4);
		return (1);
	}
	return (1);
}
