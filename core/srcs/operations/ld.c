/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/13 04:20:15 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_ld(t_champ *champ, t_proces *proces, t_arg *args)
{
	champ = NULL;
	proces->reg[args[1].value] = args[0].value;
	proces->carry = proces->reg[args[1].value] == 0 ? 1 : 0;
	return (1);
}
