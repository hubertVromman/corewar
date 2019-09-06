/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:51:18 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/11 06:21:41 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_sub(t_champ *champ, t_proces *proces, t_arg *args)
{
	champ = NULL;
	proces->reg[args[2].value] =
		proces->reg[args[0].value] - proces->reg[args[1].value];
	proces->carry = proces->reg[args[2].value] == 0 ? 1 : 0;
	return (1);
}
