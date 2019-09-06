/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:49:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/11 06:22:42 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_add(t_champ *champ, t_proces *pro, t_arg *args)
{
	champ = NULL;
	pro->reg[args[2].value] = pro->reg[args[0].value] + pro->reg[args[1].value];
	pro->carry = pro->reg[args[2].value] == 0 ? 1 : 0;
	return (1);
}
