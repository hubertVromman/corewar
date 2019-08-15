/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:02 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/14 23:01:35 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_aff(t_champ *champ, t_proces *proces, t_arg *args)
{
	champ = NULL;
	ft_printf("%c", proces->reg[args[0].value]);
	proces->carry = proces->reg[args[0].value] == 0 ? 1 : 0;
	return (1);
}
