/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:39:55 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/04 23:19:55 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		fill_instuctions(void)
{
	int pos;

	pos = g_all.visu.nb_cols * (HEADER_HEIGHT + 3) - 50;
	add_str_to_buffer(g_all.visu.current_frame + pos, "- Speed +/-  1 cps          'e' | 'w'", WHITE, 0);
	add_str_to_buffer(g_all.visu.current_frame + pos + g_all.visu.nb_cols , "- Speed +/- 10 cps          'r' | 'q'", WHITE, 0);
	add_str_to_buffer(g_all.visu.current_frame + pos + (g_all.visu.nb_cols * 2), "- Speed @ 1000 cps          'm'", WHITE, 0);
	add_str_to_buffer(g_all.visu.current_frame + pos + (g_all.visu.nb_cols * 3), "- Pause                     'space'", WHITE, 0);
	add_str_to_buffer(g_all.visu.current_frame + pos + (g_all.visu.nb_cols * 4), "- Display flamme            'f'", WHITE, 0);
	return (0);
}

int		fill_current_frame(void)
{
	fill_border();
	fill_header();
	fill_memory();
	fill_player_info();
	fill_process_info();
	fill_instuctions();
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

static int		fill_waves()
{
	int i;

	i = -1;
	jump_to(g_all.visu.nb_cols - INFO_WIDTH + 4, HEADER_HEIGHT);
	while (++i < 3)
		ft_printf(RESET_COLOR "%S", DECO_1);
	ft_printf(" { Info Players } ");
	i = -1;
	while (++i < 3)
		ft_printf(RESET_COLOR "%S", DECO_1);
	i = -1;
	jump_to(g_all.visu.nb_cols - INFO_WIDTH + 4, HEADER_HEIGHT + 19);
	while (++i < 3)
		ft_printf(RESET_COLOR "%S", DECO_1);
	ft_printf(" { All Process } ");
	i = -1;
	while (++i < 3)
		ft_printf(RESET_COLOR "%S", DECO_1);
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
	fill_waves();
	return (0);
}
