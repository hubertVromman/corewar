/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:02 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/04 23:18:31 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_new_char(char to_print, int off_x, int off_y)
{
	if (!(g_all.visu.aff_s = realloc(g_all.visu.aff_s, g_all.visu.size_s + 1)))
		exit_func(MERROR, 0);
	g_all.visu.aff_s[g_all.visu.size_s] = to_print;
	if (g_all.visu.size_s)
		write_to_buf(g_all.visu.next_frame + off_y * g_all.visu.nb_cols + off_x
			+ 5 + g_all.visu.size_s, g_all.visu.aff_s[g_all.visu.size_s - 1],
			WHITE, 0);
	g_all.visu.size_s++;
	return (0);
}

int		visu_aff(char to_print, int color)
{
	int		off_x;
	int		off_y;

	off_x = g_all.visu.nb_cols - INFO_WIDTH + 4;
	off_y = HEADER_HEIGHT + 7;
	if (g_all.visu.size_s == INFO_WIDTH - 14)
	{
		ft_memcpy(g_all.visu.aff_s, g_all.visu.aff_s + 1,
			g_all.visu.size_s - 1);
		g_all.visu.aff_s[g_all.visu.size_s - 1] = to_print;
		add_str_to_buf(g_all.visu.next_frame + off_y * g_all.visu.nb_cols +
			off_x + 6, g_all.visu.aff_s, WHITE, 0);
	}
	else
	{
		print_new_char(to_print, off_x, off_y);
	}
	write_to_buf(g_all.visu.next_frame + off_y * g_all.visu.nb_cols + off_x +
		5 + g_all.visu.size_s, to_print, color, 0);
	return (0);
}

int		operation_aff(t_champ *champ, t_proces *proces, t_arg *args)
{
	char	to_print;

	to_print = proces->reg[args[0].value];
	champ = NULL;
	if (g_all.flags[VISU])
	{
		if (to_print < 32 || to_print >= 127)
			to_print = ' ';
		visu_aff(to_print, proces->color_rgb);
	}
	else if (g_all.flags[INFORMATION])
		ft_printf("Aff: %c\n", to_print);
	proces->carry = proces->reg[args[0].value] == 0 ? 1 : 0;
	return (1);
}
