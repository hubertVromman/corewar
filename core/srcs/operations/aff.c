/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:02 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/28 21:17:30 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_aff(t_champ *champ, t_proces *proces, t_arg *args)
{
	champ = NULL;
	if (args[0].value > REG_NUMBER || args[0].value < 1)
	{
		return (-1);
	}
	else
	{
		ft_printf("%c", proces->reg[args[0].value - 1]);
		return (1);
	}
}
