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

int		print_border()
{
	int i;

	i = -1;
	while (++i < SCREEN_HEIGHT) // vertical lines
	{
		write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * (i + 1) - 1, ' ', 0, BORDER_COLOR);
		write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * (i + 1) - 2, ' ', 0, BORDER_COLOR);
		if (i >= HEADER_HEIGHT - 2)
		{
			write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * (i + 1) - 102, ' ', 0, BORDER_COLOR);
			write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * (i + 1) - 103, ' ', 0, BORDER_COLOR);
		}
		write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * i, ' ', 0, BORDER_COLOR);
		write_to_buffer(g_all.visu.current_frame + g_all.visu.nb_cols * i + 1, ' ', 0, BORDER_COLOR);

	}
	i = -1;
	while (++i < g_all.visu.nb_cols) // horizontal lines
	{
		write_to_buffer(g_all.visu.current_frame + 0 * g_all.visu.nb_cols + i, ' ', 0, BORDER_COLOR);
		write_to_buffer(g_all.visu.current_frame + 8 * g_all.visu.nb_cols + i, ' ', 0, BORDER_COLOR);
		write_to_buffer(g_all.visu.current_frame + SCREEN_HEIGHT * g_all.visu.nb_cols + i, ' ', 0, BORDER_COLOR);
	}
	return (0);
}

int		print_header()
{
	int		offset_x;

	offset_x = g_all.visu.nb_cols / 2 - 21;
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 1, "   _____                                  ", 0x999999, 0);
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 2, "  / ____|                                 ", 0x999999, 0);
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 3, " | |     ___  _ __ _____      ____ _ _ __ ", 0x999999, 0);
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 4, " | |    / _ \\| '__/ _ \\ \\ /\\ / / _` | '__|", 0x999999, 0);
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 5, " | |___| (_) | | |  __/\\ V  V / (_| | |   ", 0x999999, 0);
	add_string_to_buffer(g_all.visu.current_frame + offset_x + g_all.visu.nb_cols * 6, "  \\_____\\___/|_|  \\___| \\_/\\_/ \\__,_|_|   ", 0x999999, 0);
	return (0);
}

int		fill_current_frame()
{
	char		*tmp;
	int			offset_x;
	t_printable	*starting_point;

	print_border();
	print_header();
	offset_x = g_all.visu.nb_cols - INFO_WIDTH + 3;
	starting_point = g_all.visu.current_frame + HEADER_HEIGHT * g_all.visu.nb_cols + offset_x;
	tmp = NULL;
	if (ft_printf("%1$/43c Info %1$/43c %#>", '-', &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(starting_point, tmp, WHITE, 0);
	free(tmp);
	add_string_to_buffer(starting_point + 1 * g_all.visu.nb_cols, "Cycles              :", WHITE, 0);
	add_string_to_buffer(starting_point + 2 * g_all.visu.nb_cols, "Cycles/second limit :", WHITE, 0);
	add_string_to_buffer(starting_point + 3 * g_all.visu.nb_cols, "Nbr of process      :", WHITE, 0);
	add_string_to_buffer(starting_point + 4 * g_all.visu.nb_cols, "Lives period        :", WHITE, 0);
	add_string_to_buffer(starting_point + 5 * g_all.visu.nb_cols, "Cycle to die        :", WHITE, 0);
	add_string_to_buffer(starting_point + 6 * g_all.visu.nb_cols, "Aff :", WHITE, 0);
	if (ft_printf("%1$/40c ALL proces %1$/40c %#>", '-', &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(starting_point + 18 * g_all.visu.nb_cols, tmp, WHITE, 0);
	free(tmp);

	for (int i = 0; i < g_all.nb_champ; i++)
	{
		starting_point = g_all.visu.current_frame + (HEADER_HEIGHT + i % 2 * 5) * g_all.visu.nb_cols + offset_x + i / 2 * 51;
		if (ft_printf("PLAYER %3d :%#>", g_all.champ[i].player_nb, &tmp) == -1)
			exit_func(MERROR, 0);
		add_string_to_buffer(starting_point + 8 * g_all.visu.nb_cols, tmp, WHITE, 0);
		free(tmp);
		if (ft_printf("%s%#>", g_all.champ[i].player_name, &tmp) == -1)
			exit_func(MERROR, 0);
		add_name_to_buffer(starting_point + 8 * g_all.visu.nb_cols + 13, tmp, g_all.champ[i].color_rgb, 0);
		free(tmp);
		add_string_to_buffer(starting_point + 9 * g_all.visu.nb_cols + 5, "Last live", WHITE, 0);
		add_string_to_buffer(starting_point + 10 * g_all.visu.nb_cols + 5, "Lives period", WHITE, 0);
		add_string_to_buffer(starting_point + 11 * g_all.visu.nb_cols + 5, "Nbr of process", WHITE, 0);
	}
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

int		init_current_frame()
{
	int i;
	int p;
	int pos;
	char *buf = NULL;

	i = -1;
	p = 0;
	while (++i < MEM_SIZE)
	{
		if (i == g_all.champ[p].proces->pc)
		{
			while (i < g_all.champ[p].proces->pc + g_all.champ[p].exec_size)
			{
				if (ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[i], &buf) == -1)
					exit_func(MERROR, 0);
				add_string_to_buffer(g_all.visu.current_frame + jump_to_buf(i), buf, g_all.champ[p].proces->color_rgb, 0);
				free(buf);
				i++;
			}
			if (p < g_all.nb_champ - 1)
				p++;
		}
		add_string_to_buffer(g_all.visu.current_frame + jump_to_buf(i), "00", VM_COLOR, 0);
	}
	fill_current_frame();
	for (int j = 0; j < g_all.nb_champ; j++)
	{
		pos = jump_to_buf(g_all.champ[j].proces->pc);
		invert_fore_and_back(&(g_all.visu.current_frame[pos]));
		invert_fore_and_back(&(g_all.visu.current_frame[pos + 1]));
	}
	ft_memcpy(g_all.visu.current_frame_flame, g_all.visu.current_frame, g_all.visu.screen_size * sizeof(t_printable));
	for (int j = 0 ; j < g_all.visu.screen_size; j++)
		print_char(g_all.visu.current_frame[j], j);
	return (0);
}
