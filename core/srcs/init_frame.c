/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:39:55 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/28 01:39:57 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		fill_current_frame(void)
{
	fill_border();
	fill_header();
	fill_memory();
	fill_player_info();
	fill_process_info();
	return (0);
}

int		invert_fore_and_back(t_printable *printable)
{
	int		tmp;

	tmp = printable->fore_color;
	printable->fore_color = printable->back_color;
	printable->back_color = tmp;
	return (0);
}

int		init_current_frame(void)
{
	int		pos;
	int		i;

	fill_current_frame();
	i = -1;
	while (++i < g_all.nb_champ)
	{
		pos = jump_to_buf(g_all.champ[i].proces->pc);
		invert_fore_and_back(&(g_all.visu.current_frame[pos]));
		invert_fore_and_back(&(g_all.visu.current_frame[pos + 1]));
	}
	ft_memcpy(g_all.visu.current_frame_flame, g_all.visu.current_frame,
			g_all.visu.screen_size * sizeof(t_printable));
	i = -1;
	while (++i < g_all.visu.screen_size)
		print_char(g_all.visu.current_frame[i], i);
	return (0);
}
