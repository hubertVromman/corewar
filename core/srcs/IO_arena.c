/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:44:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/28 01:44:27 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		increment_pc(t_proces *proces, int nb_byte)
{
	int pos;
	char *buf = NULL;

	if (g_all.flags[VISU])
	{
		pos = jump_to_buf(proces->pc);
		if (ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[proces->pc], &buf) == -1)
			exit_func(MERROR, 0);
		write_to_buf(g_all.visu.next_frame + pos, buf[0], g_all.color[proces->pc], 0);
		write_to_buf(g_all.visu.next_frame + pos + 1, buf[1], g_all.color[proces->pc], 0);
		free(buf);
	}
	proces->pc = calc_pc(proces->pc + nb_byte);
	if (g_all.flags[VISU])
	{
		pos = jump_to_buf(proces->pc);
		ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[proces->pc], &buf);
		write_to_buf(g_all.visu.next_frame + pos, buf[0], 0, proces->color_rgb);
		write_to_buf(g_all.visu.next_frame + pos + 1, buf[1], 0, proces->color_rgb);
		free(buf);
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
		if (ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[address], &buf) == -1)
			exit_func(MERROR, 0);
		write_to_buf(g_all.visu.next_frame + pos, buf[0], proces->color_rgb, 0);
		write_to_buf(g_all.visu.next_frame + pos + 1, buf[1], proces->color_rgb, 0);
		g_all.color[address] = proces->color_rgb;
		free(buf);
	}
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
