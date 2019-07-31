/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:51:38 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/23 15:07:54 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		calc_pc(int pc)
{
	pc %= MEM_SIZE;
	return (pc);
}

int		increment_pc(t_proces *proces, int nb_byte)
{
	proces->pc = (proces->pc + nb_byte) % MEM_SIZE;
	return (proces->pc);
}

int		write_byte(t_proces *proces, int address, char to_write)
{
	address %= MEM_SIZE;
	g_all.arena[address] = to_write;
	proces = NULL;
	return (0);
}

int		write_int(t_proces *proces, int address, int to_write)
{
	write_byte(proces, address, to_write >> 24);
	write_byte(proces, address + 1, to_write >> 16);
	write_byte(proces, address + 2, to_write >> 8);
	write_byte(proces, address + 3, to_write);
	return (0);
}

char	get_codage(int opcode)
{
	char	codage;
	int		i;

	codage = 0;
	i = -1;
	while (++i < g_op_tab[opcode - 1].nb_params)
	{
		if (g_op_tab[opcode - 1].param[i] & (T_IND | T_DIR))
			codage |= 1 << (7 - 2 * i);
		if (g_op_tab[opcode - 1].param[i] & (T_IND | T_REG))
			codage |= 1 << (6 - 2 * i);
	}
	return (codage);
}

int		get_ind(int *pc)
{
	int		first_char;
	int		second_char;
	int		initial_pc;

	initial_pc = *pc;
	first_char = (g_all.arena[calc_pc((*pc)++)] & 0xff) << 8;
	second_char = g_all.arena[calc_pc((*pc)++)] & 0xff;
	return (g_all.arena[calc_pc(initial_pc + (short)(first_char | second_char))]);
}

int		read_byte(int pc, int size)
{
	int res;
	int i;

	i = -1;
	res = 0;
	while(++i < size)
	{
		res <<= 8;
		res |= g_all.arena[calc_pc(pc  + i)];
	}
	return (res);
}

t_arg	*get_arguments(t_proces *proces)
{
	static t_arg	to_return[MAX_ARGS_NUMBER];
	int				i;
	int				j;
	int				tmp_pc;
	int				opcode;
	int				codage;

	tmp_pc = proces->pc;
	opcode = g_all.arena[tmp_pc++];
	codage = g_op_tab[opcode - 1].codage ? g_all.arena[calc_pc(tmp_pc++)] : get_codage(opcode);
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		if ((codage & 1 << (7 - 2 * i)) && (codage & 1 << (6 - 2 * i))) // 11 -> IND
		{
			if (g_op_tab[opcode - 1].nb_params < i || !(g_op_tab[opcode - 1].param[i] & T_IND))
				return (NULL);
			to_return[i].type = T_IND;
			to_return[i].size = 2;
			to_return[i].value = get_ind(&tmp_pc);
		}
		else if (codage & 1 << (7 - 2 * i)) // 10 -> DIR
		{
			if (g_op_tab[opcode - 1].nb_params < i || !(g_op_tab[opcode - 1].param[i] & T_DIR))
				return (NULL);
			to_return[i].type = T_DIR;
			to_return[i].size = 4 - 2 * g_op_tab[opcode - 1].dir_size;
			to_return[i].value = 0;
			j = -1;
			while (++j < to_return[i].size)
				to_return[i].value |= (g_all.arena[calc_pc(tmp_pc++)] & 0xff) << (to_return[i].size - j - 1) * 8;
			if (to_return[i].size == 2)
				to_return[i].value = (short)to_return[i].value;
		}
		else if (codage & 1 << (6 - 2 * i)) // 01 -> REG
		{
			if (g_op_tab[opcode - 1].nb_params < i || !(g_op_tab[opcode - 1].param[i] & T_REG))
				return (NULL);
			to_return[i].type = T_REG;
			to_return[i].size = 1;
			to_return[i].value = g_all.arena[calc_pc(tmp_pc++)] - 1;
			if (to_return[i].value >= REG_NUMBER || to_return[i].value < 0)
				return (NULL);
		}
		else if (i < g_op_tab[opcode - 1].nb_params) // pas assez d'arguments
		{
			return (NULL);
		}
		else if (codage) // si trop d'arguments
		{
			return (NULL);
		}
		else
		{
			to_return[i].type = 0;
			to_return[i].size = 0;
			to_return[i].value = 0;
		}
		codage &= 0x00ffffff >> i;
	}
	return (to_return);
}
