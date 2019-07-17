/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:51:38 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/16 15:51:40 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_arg	*get_argument_size(int pc)
{
	static t_arg	to_return[MAX_ARGS_NUMBER];
	int				i;

	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		if ((codage & 1 << (7 - 2 * i)) && (codage & 1 << (6 - 2 * i)))
		{
			to_return[i].type = T_IND;
			to_return[i].size = 2;
		}
		else if (codage & 1 << (7 - 2 * i))
		{
			to_return[i].type = T_DIR;
			to_return[i].size = 4 - 2 * g_op_tab[opcode - 1].dir_size;
		}
		else if (codage & 1 << (6 - 2 * i))
		{
			to_return[i].type = T_REG;
			to_return[i].size = 1;
		}
		else
		{
			to_return[i].type = 0;
			to_return[i].size = 0;
			to_return[i].value = 0;
		}
	}
	return (to_return);
}

int		increment_pc(int pc)
{
	return ((pc + 1) % MEM_SIZE);
}
