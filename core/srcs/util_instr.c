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

int		calc_pc(int pc)
{
	if (pc > MEM_SIZE)
		pc %= MEM_SIZE;
	return (pc);
}

int		increment_pc(int *pc, int nb_byte)
{
	*pc = (*pc + nb_byte) % MEM_SIZE;
	return (*pc);
}

char	get_codage(int opcode)
{
	char	codage;
	int		i;

	codage = 0;
	i = -1;
	while (++i < g_op_tab[opcode - 1].param_nb)
	{
		if (g_op_tab[opcode - 1].param[i] & (T_IND | T_DIR))
			codage |= 1 << (7 - 2 * i);
		if (g_op_tab[opcode - 1].param[i] & (T_IND | T_REG))
			codage |= 1 << (6 - 2 * i);
	}
	return (codage);
}

t_arg	*get_arguments(int *pc)
{
	static t_arg	to_return[MAX_ARGS_NUMBER];
	int				i;
	int				j;
	int				opcode;
	int				codage;

	opcode = g_all.arena[*pc];
	codage = g_op_tab[opcode - 1].codage ? g_all.arena[increment_pc(pc, 1)] : get_codage(opcode);
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		if ((codage & 1 << (7 - 2 * i)) && (codage & 1 << (6 - 2 * i)))
		{
			if (g_op_tab[opcode - 1].param_nb < i || !(g_op_tab[opcode - 1].param[i] & T_IND))
				return (NULL);
			to_return[i].type = T_IND;
			to_return[i].size = 2;
			to_return[i].value = g_all.arena[increment_pc(pc, 1)] << 8 | g_all.arena[increment_pc(pc, 1)];
		}
		else if (codage & 1 << (7 - 2 * i))
		{
			if (g_op_tab[opcode - 1].param_nb < i || !(g_op_tab[opcode - 1].param[i] & T_DIR))
				return (NULL);
			to_return[i].type = T_DIR;
			to_return[i].size = 4 - 2 * g_op_tab[opcode - 1].dir_size;
			to_return[i].value = 0;
			j = -1;
			while (++j < to_return[i].size)
				to_return[i].value |= (g_all.arena[increment_pc(pc, 1)] & 0xff) << (to_return[i].size - j - 1) * 8;
		}
		else if (codage & 1 << (6 - 2 * i))
		{
			if (g_op_tab[opcode - 1].param_nb < i || !(g_op_tab[opcode - 1].param[i] & T_REG))
				return (NULL);
			to_return[i].type = T_REG;
			to_return[i].size = 1;
			to_return[i].value = g_all.arena[increment_pc(pc, 1)];
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
