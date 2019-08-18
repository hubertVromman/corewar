/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:51:38 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/15 06:32:29 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		calc_pc(int pc)
{
	return ((pc + MEM_SIZE) % MEM_SIZE);
}

int		increment_pc(t_proces *proces, int nb_byte)
{
	int pos;
	char *buf = NULL;

	if (g_all.flags[VISU])
	{
		pos = jump_to_buf(proces->pc);
		ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[proces->pc], &buf);
		write_to_buffer(g_all.visu.next_frame + pos + 1, buf[0], g_all.color[proces->pc], 0);
		write_to_buffer(g_all.visu.next_frame + pos + 2, buf[1], g_all.color[proces->pc], 0);
	}
	proces->pc = calc_pc(proces->pc + nb_byte);
	if (g_all.flags[VISU])
	{
		pos = jump_to_buf(proces->pc);
		ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[proces->pc], &buf);
		write_to_buffer(g_all.visu.next_frame + pos + 1, buf[0], 0, proces->color_rgb);
		write_to_buffer(g_all.visu.next_frame + pos + 2, buf[1], 0, proces->color_rgb);
	}
	return (proces->pc);
}

int		write_byte(t_proces *proces, int address, char to_write)
{
	int pos;
	char *buf = NULL;

	address = calc_pc(address);
	g_all.arena[address] = to_write;
	if (g_all.flags[VISU])
	{
		pos = jump_to_buf(address);
		int fd = open ("f", O_CREAT | O_APPEND | O_RDWR, 0755);
		ft_printf("%d %d\n%>", address, pos, fd);
		ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[address], &buf);
		write_to_buffer(g_all.visu.next_frame + pos + 1, buf[0], proces->color_rgb, 0);
		write_to_buffer(g_all.visu.next_frame + pos + 2, buf[1], proces->color_rgb, 0);
		g_all.color[address] = proces->color_rgb;
	}
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
	if (!opcode)
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

int		get_ind(int *pc, int mod, int no_go, int one_byte)
{
	int		first_char;
	int		second_char;
	int		initial_pc;

	initial_pc = *pc;
	first_char = (g_all.arena[calc_pc((*pc)++)] & 0xff) << 8;
	second_char = g_all.arena[calc_pc((*pc)++)] & 0xff;
	if (no_go)
		return ((short)(first_char | second_char));
	return (read_byte(calc_pc(initial_pc - (one_byte ? 4 : 2) + (mod ? (short)(first_char | second_char) % IDX_MOD : (short)(first_char | second_char))), one_byte ? 1 : 4)); // (one_byte ? 4 : 2) a ete modifier, a verifier
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
		res |= g_all.arena[calc_pc(pc + i)] & 0xff;
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
	if (opcode < 1 || opcode > 16)
		return (NULL);
	codage = g_op_tab[opcode - 1].codage ? g_all.arena[calc_pc(tmp_pc++)] : get_codage(opcode);
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		if ((codage & 1 << (7 - 2 * i)) && (codage & 1 << (6 - 2 * i))) // 11 -> IND
		{
			if (i >= g_op_tab[opcode - 1].nb_params || g_op_tab[opcode - 1].nb_params < i || !(g_op_tab[opcode - 1].param[i] & T_IND)) // trop de param ou wrong type
			{
				return (NULL);
			}
			to_return[i].type = T_IND;
			to_return[i].size = 2;
			to_return[i].value = get_ind(&tmp_pc, opcode != LLD_OP && opcode != LLDI_OP, opcode == ST_OP, opcode == STI_OP);
		}
		else if (codage & 1 << (7 - 2 * i)) // 10 -> DIR
		{
			if (i >= g_op_tab[opcode - 1].nb_params || g_op_tab[opcode - 1].nb_params < i || !(g_op_tab[opcode - 1].param[i] & T_DIR))
			{
				return (NULL);
			}
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
			if (i >= g_op_tab[opcode - 1].nb_params || g_op_tab[opcode - 1].nb_params < i || !(g_op_tab[opcode - 1].param[i] & T_REG))
			{
				return (NULL);
			}
			to_return[i].type = T_REG;
			to_return[i].size = 1;
			to_return[i].value = g_all.arena[calc_pc(tmp_pc++)] - 1;
			if (to_return[i].value >= REG_NUMBER || to_return[i].value < 0)
			{
				return (NULL);
			}
		}
		else if (i < g_op_tab[opcode - 1].nb_params) // pas assez d'arguments
		{
			return (NULL);
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
