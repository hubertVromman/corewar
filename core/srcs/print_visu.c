/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:55:57 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/28 01:55:59 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		copy_and_print_buffer(t_printable *dst, t_printable *src, int size)
{
	for (int l = 0; l < size; l++)
	{
		if (src[l].to_print && ft_memcmp(src + l, dst + l, sizeof(t_printable)))
		{
			ft_memcpy(dst + l, src + l, sizeof(t_printable));
			print_char(dst[l], l);
		}
	}
	return (0);
}

int		print_frame_diff()
{
	for (int l = 0; l < g_all.visu.screen_size; l++)
	{
		if (g_all.visu.next_frame[l].to_print && ft_memcmp(g_all.visu.next_frame + l, g_all.visu.current_frame + l, sizeof(t_printable)))
		{
			ft_memcpy(g_all.visu.current_frame + l, g_all.visu.next_frame + l, sizeof(t_printable));
		}
	}
	if (g_all.visu.flame)
		for (int l = 0; l < FLAME_HEIGHT * g_all.visu.nb_cols; l++)
		{
			if (g_all.visu.flame_buf[l].to_print)
				ft_memcpy(g_all.visu.next_frame + g_all.visu.offset_flame_y * g_all.visu.nb_cols + l, g_all.visu.flame_buf + l, sizeof(t_printable));
			if (!(g_all.visu.next_frame[g_all.visu.offset_flame_y * g_all.visu.nb_cols + l].to_print))
				g_all.visu.next_frame[g_all.visu.offset_flame_y * g_all.visu.nb_cols + l].to_print = ' ';
		}
	else if (!g_all.end)
		ft_memcpy(g_all.visu.next_frame, g_all.visu.flame_buf, sizeof(t_printable) * g_all.visu.screen_size);
	copy_and_print_buffer(g_all.visu.current_frame_flame, g_all.visu.next_frame, g_all.visu.screen_size);
	return (0);
}

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
		ft_printf(RGB_PRINT, (f_color >> 16) & 0xff, (f_color >> 8) & 0xff, (f_color >> 0) & 0xff);
		g_all.visu.previous_fg = f_color;
	}
	if (g_all.visu.previous_bg != b_color)
	{
		ft_printf(RGB_PRINT_BG, (b_color >> 16) & 0xff, (b_color >> 8) & 0xff, (b_color >> 0) & 0xff);
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
	insta_print_char(printable.to_print, printable.fore_color, printable.back_color, pos);
	return (0);
}
