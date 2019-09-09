/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:16:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/04 23:19:24 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_cycle_left(int opcode)
{
	if (opcode < 1 || opcode > NB_OPERATIONS)
		return (1);
	else
		return (g_op_tab[opcode - 1].cycle_op);
}

int		calc_pc(int pc)
{
	return ((pc + MEM_SIZE) % MEM_SIZE);
}

int		read_arena_op(int pc)
{
	int		opcode;

	opcode = g_all.arena[pc];
	if (opcode < 1 || opcode > NB_OPERATIONS)
		return (0);
	return (opcode);
}

char	get_codage(int opcode)
{
	char	codage;
	int		i;

	codage = 0;
	i = -1;
	if (opcode < 1 || opcode >= NB_OPERATIONS)
		return (0);
	while (++i < g_op_tab[opcode - 1].nb_params)
	{
		if (g_op_tab[opcode - 1].param[i] & (T_IND | T_DIR))
			codage |= 1 << (7 - 2 * i);
		if (g_op_tab[opcode - 1].param[i] & (T_IND | T_REG))
			codage |= 1 << (6 - 2 * i);
	}
	return (codage);
}

int		dump_memory(void)
{
	int		i;
	char	*buffer;
	char	*s;

	if (!(s = malloc((MEM_SIZE * 3) + 576)))
		exit_func(MERROR, 0);
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!i || !(i % 64))
		{
			if ((ft_printf("%.4p : %#>", i, &buffer) == -1))
				exit_func(MERROR, 0);
			ft_memcpy((s + (i / 64) * 9 + i * 3), buffer, 9);
			free(buffer);
		}
		if (ft_printf(CHAR_HEX_PRINT "%c%#>", g_all.arena[i], (i + 1) %
			64 ? ' ' : '\n', &buffer) == -1)
			exit_func(MERROR, 0);
		ft_memcpy(s + (i / 64) * 9 + 9 + i * 3, buffer, 3);
		free(buffer);
	}
	write(1, s, (MEM_SIZE * 3) + 576);
	free(s);
	return (0);
}
