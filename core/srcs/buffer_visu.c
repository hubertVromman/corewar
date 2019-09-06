/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 17:40:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/06 17:40:26 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		copy_and_print_buffer(t_printable *dst, t_printable *src, int size)
{
	int l;

	l = -1;
	while (++l < size)
	{
		if (src[l].to_print && ft_memcmp(src + l, dst + l, sizeof(t_printable)))
		{
			ft_memcpy(dst + l, src + l, sizeof(t_printable));
			print_char(dst[l], l);
		}
	}
	return (0);
}

int		print_frame_diff_flame(void)
{
	int l;

	l = -1;
	while (++l < FLAME_HEIGHT * g_all.visu.nb_cols)
	{
		if (g_all.visu.flame_buf[l].to_print)
			ft_memcpy(g_all.visu.next_frame + g_all.visu.offset_flame_y *
				g_all.visu.nb_cols + l, g_all.visu.flame_buf +
				l, sizeof(t_printable));
		if (!(g_all.visu.next_frame[g_all.visu.offset_flame_y *
			g_all.visu.nb_cols + l].to_print))
			g_all.visu.next_frame[g_all.visu.offset_flame_y *
			g_all.visu.nb_cols + l].to_print = ' ';
	}
	return (0);
}

int		print_frame_diff(void)
{
	int l;

	l = -1;
	while (++l < g_all.visu.screen_size)
		if (g_all.visu.next_frame[l].to_print && ft_memcmp(g_all.visu.next_frame
			+ l, g_all.visu.current_frame + l, sizeof(t_printable)))
			ft_memcpy(g_all.visu.current_frame + l, g_all.visu.next_frame + l,
				sizeof(t_printable));
	if (g_all.end && g_all.end != g_all.cycle)
		ft_memcpy(g_all.visu.next_frame, g_all.visu.flame_buf,
			sizeof(t_printable) * g_all.visu.screen_size);
	else if (g_all.visu.flame)
		print_frame_diff_flame();
	copy_and_print_buffer(g_all.visu.current_frame_flame, g_all.visu.next_frame,
		g_all.visu.screen_size);
	return (0);
}
