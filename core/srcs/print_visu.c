/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:55:57 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/31 07:29:34 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		insta_print_char(char c, int f_color, int b_color, int pos)
{
	pos = pos % g_all.visu.screen_size;
	if (g_all.visu.previous_pos + 1 != pos)
	{
		jump_to(pos % g_all.visu.nb_cols, pos / g_all.visu.nb_cols);
		g_all.visu.previous_pos = pos;
	}
	else
		g_all.visu.previous_pos++;
	if (g_all.visu.previous_fg != f_color)
	{
		ft_printf(RGB_PRINT, (f_color >> 16) & 0xff, (f_color >> 8) &
			0xff, (f_color >> 0) & 0xff);
		g_all.visu.previous_fg = f_color;
	}
	if (g_all.visu.previous_bg != b_color)
	{
		ft_printf(RGB_PRINT_BG, (b_color >> 16) & 0xff, (b_color >> 8) &
			0xff, (b_color >> 0) & 0xff);
		g_all.visu.previous_bg = b_color;
	}
	ft_printf("%c", c);
	return (0);
}

int		insta_print_string(char *s, int f_color, int b_color, int pos)
{
	int		i;

	i = -1;
	while (s[++i])
		insta_print_char(s[i], f_color, b_color, pos++);
	return (0);
}

int		print_char(t_printable printable, int pos)
{
	insta_print_char(printable.to_print, printable.fore_color,
		printable.back_color, pos);
	return (0);
}
