/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:51:38 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/10 05:28:36 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int
	get_ind(int *pc, int mod, int no_go, int sti)
{
	int		first_char;
	int		second_char;
	int		initial_pc;

	initial_pc = *pc;
	first_char = (g_all.arena[calc_pc((*pc)++)] & 0xff) << 8;
	second_char = g_all.arena[calc_pc((*pc)++)] & 0xff;
	if (no_go)
		return ((short)(first_char | second_char));
	return (read_byte(calc_pc(initial_pc - (sti ? 3 : 2) +
		(mod ? ((short)(first_char | second_char)) % IDX_MOD :
		(short)(first_char | second_char))), 4));
}

static t_arg
	*get_single_argument3(int arg_idx, int *tmp_pc, int opcode, char codage)
{
	static t_arg	to_return;

	ft_bzero(&to_return, sizeof(to_return));
	to_return.valid = 1;
	if (codage & 1 << (6 - 2 * arg_idx))
	{
		to_return.size = 1;
		if (arg_idx >= g_op_tab[opcode - 1].nb_params)
			to_return.valid = 0;
		else if (!(g_op_tab[opcode - 1].param[arg_idx] & T_REG))
		{
			g_all.arglen += to_return.size;
			to_return.valid = 0;
		}
		else
			g_all.arglen += to_return.size;
		to_return.type = T_REG;
		to_return.value = g_all.arena[calc_pc((*tmp_pc)++)] - 1;
		if (to_return.value >= REG_NUMBER || to_return.value < 0)
			to_return.valid = 0;
	}
	else if (arg_idx < g_op_tab[opcode - 1].nb_params)
		to_return.valid = 0;
	return (&to_return);
}

static t_arg
	*get_single_argument2(int arg_idx, int *tmp_pc, int opcode, char codage)
{
	static t_arg	to_return;
	int				j;

	to_return.valid = 1;
	if (codage & 1 << (7 - 2 * arg_idx))
	{
		to_return.size = 4 - 2 * g_op_tab[opcode - 1].dir_size;
		if (arg_idx >= g_op_tab[opcode - 1].nb_params)
			to_return.valid = 0;
		else if (g_all.arglen += to_return.size)
			if (!(g_op_tab[opcode - 1].param[arg_idx] & T_DIR))
				to_return.valid = 0;
		to_return.type = T_DIR;
		to_return.value = 0;
		j = -1;
		while (++j < to_return.size)
			to_return.value |= (g_all.arena[calc_pc((*tmp_pc)++)] & 0xff)
				<< (to_return.size - j - 1) * 8;
		if (to_return.size == 2)
			to_return.value = (short)to_return.value;
		return (&to_return);
	}
	else
		return (get_single_argument3(arg_idx, tmp_pc, opcode, codage));
}

static t_arg
	*get_single_argument(int arg_idx, int *tmp_pc, int opcode, char codage)
{
	static t_arg	to_return;

	to_return.valid = 1;
	if ((codage & 1 << (7 - 2 * arg_idx)) && (codage & 1 << (6 - 2 * arg_idx)))
	{
		to_return.size = 2;
		if (arg_idx >= g_op_tab[opcode - 1].nb_params)
		{
			to_return.valid = 0;
		}
		else if (!(g_op_tab[opcode - 1].param[arg_idx] & T_IND))
		{
			g_all.arglen += to_return.size;
			to_return.valid = 0;
		}
		else
			g_all.arglen += to_return.size;
		to_return.type = T_IND;
		to_return.value = get_ind(tmp_pc, opcode != LLD_OP &&
			opcode != LLDI_OP, opcode == ST_OP, opcode == STI_OP);
		return (&to_return);
	}
	else
		return (get_single_argument2(arg_idx, tmp_pc, opcode, codage));
}

t_arg
	*get_arguments(t_proces *proces)
{
	static t_arg	to_return[MAX_ARGS_NUMBER];
	int				i;
	int				tmp_pc;
	int				opcode;
	char			codage;

	tmp_pc = proces->pc;
	tmp_pc++;
	opcode = proces->opcode;
	if (opcode < 1 || opcode > NB_OPERATIONS)
		return (NULL);
	codage = g_op_tab[opcode - 1].codage ? g_all.arena[calc_pc(tmp_pc++)]
		: get_codage(opcode);
	i = -1;
	g_all.arglen = g_op_tab[opcode - 1].codage + 1;
	while (++i < MAX_ARGS_NUMBER)
	{
		ft_memcpy(&(to_return[i]),
			get_single_argument(i, &tmp_pc, opcode, codage), sizeof(t_arg));
	}
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
		if (to_return[i].valid == 0)
			return (NULL);
	return (to_return);
}
