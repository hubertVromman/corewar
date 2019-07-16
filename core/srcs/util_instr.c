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

int		*get_argument_size(int opcode, int codage)
{
	static int	to_return[MAX_ARGS_NUMBER];
	int			i;

	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		if ((codage & 1 << (7 - 2 * i)) && (codage & 1 << (6 - 2 * i)))
			to_return[i] = 2;
		else if (codage & 1 << (7 - 2 * i))
			to_return[i] = 4 - 2 * g_op_tab[opcode - 1].dir_size;
		else if (codage & 1 << (6 - 2 * i))
			to_return[i] = T_REG;
		else
			to_return[i] = 0;
	}
	return (to_return);
}