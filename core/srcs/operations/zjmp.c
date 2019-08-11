/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:26 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/11 06:14:04 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_zjmp(t_champ *champ, t_proces *proces, t_arg *args)
{
	champ = NULL;

	if (proces->carry == 1 && args[0].type & T_DIR && args[0].value)
	{
		increment_pc(proces, args[0].value);
	}
	else
	{
		increment_pc(proces, 3);
	}
	return (1);
}
