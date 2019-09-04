/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:38:07 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/04 23:19:29 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		jump_to(int x, int y)
{
	ft_printf("\e[%d;%dH", y + 1, x + 1);
	return (0);
}

void	exit_ctrl_c(int c)
{
	usleep(50 * 1000);
	c = 0;
	exit_func(0, 0);
}

int		jump_to_buf(int pc)
{
	int		offset_x;
	int		offset_y;
	int		pos;

	offset_x = MEMORY_OFFSET_X;
	offset_y = HEADER_HEIGHT;
	pc = calc_pc(pc);
	pos = (g_all.visu.nb_cols * (offset_y + pc / 64)) + (offset_x + pc % 64 * 3);
	return (pos);
}
