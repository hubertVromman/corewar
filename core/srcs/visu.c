/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:38:07 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/15 05:33:24 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		jump_to(int x, int y)
{
	ft_printf("\e[%d;%dH", y + 1, x + 1);
	return (0);
}

int		jump_to_mem(int pc)
{
	int		offset_x;
	int		offset_y;

	offset_x = 2;
	offset_y = 10;
	pc = calc_pc(pc);
	jump_to(offset_x + (pc % 64) * 3, offset_y + pc / 64);
	return (0);
}

void	exit_ctrl_c(int c)
{
	c = 0;
	ft_printf(RESTORE_SCREEN);
	exit_func(0, 0);
}

int		jump_to_buf(int pc)
{
	int		offset_x;
	int		offset_y;
	int		pos;
	int		pos_x;

	offset_x = MEMORY_OFFSET_X;
	offset_y = 10;
	pc = calc_pc(pc);
	pos_x = pc % 64;
	pos = (g_all.visu.nb_cols * (offset_y + pc / 64)) + (offset_x + pos_x * 3);
	return (pos);
}
