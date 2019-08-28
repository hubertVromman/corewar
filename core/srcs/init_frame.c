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
	char *tmp;

	tmp = NULL;
	print_border();
	print_header();
	if (ft_printf("%1$/43c Info %1$/43c %#>", '-', &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + (HEADER_HEIGHT * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	if (ft_printf("Cycles %#>", &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 1) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	if (ft_printf("Cycles/second limit %#>", &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 2) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	if (ft_printf("Nbr de proces %#>", &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 3) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	if (ft_printf("Lives period %#>", &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 4) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	if (ft_printf("Cycle to die %#>", &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 5) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);

	for(int i = 0; i < g_all.nb_champ; i++)
	{
		if (ft_printf("PLAYER %d : %#>", g_all.champ[i].player_nb, &tmp) == -1)
			exit_func(MERROR, 0);
		add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 7 + (i < 2 ? (i * 5) : (i - 2) * 5)) * g_all.visu.nb_cols + (i < 2 ? X : (X + 50))), tmp, 0x00ffffff, 0);
		free(tmp);
		if (ft_printf("%s %#>", g_all.champ[i].player_name, &tmp) == -1)
			exit_func(MERROR, 0);
		add_name_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 7 + (i < 2 ? (i * 5) : (i - 2) * 5)) * g_all.visu.nb_cols + (i < 2 ? X + 12 : X + 62)), tmp, g_all.champ[i].color_rgb, 0);
		free(tmp);
		if (ft_printf("Last lives %#>", &tmp) == -1)
			exit_func(MERROR, 0);
		add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 8 + (i < 2 ? (i * 5) : (i - 2) * 5)) * g_all.visu.nb_cols + (i < 2 ? X + 5 : X + 55)), tmp, 0x00ffffff, 0);
		free(tmp);
		if (ft_printf("Lives period %#>", &tmp) == -1)
			exit_func(MERROR, 0);
		add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 9 + (i < 2 ? (i * 5) : (i - 2) * 5)) * g_all.visu.nb_cols + (i < 2 ? X + 5 : X + 55)), tmp, 0x00ffffff, 0);
		free(tmp);
		if (ft_printf("Nbr of proces %#>", &tmp) == -1)
			exit_func(MERROR, 0);
		add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 10 + (i < 2 ? (i * 5) : (i - 2) * 5)) * g_all.visu.nb_cols + (i < 2 ? X + 5 : X + 55)), tmp, 0x00ffffff, 0);
		free(tmp);
	}

	if (ft_printf("%1$/40c ALL proces %1$/40c %#>", '-', &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 18) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
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
		pos = jump_to_buf(i);
		if (i >= g_all.champ[p].proces->pc && i < (g_all.champ[p].proces->pc + g_all.champ[p].exec_size))
		{
			ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[i], &buf);
			write_to_buffer(g_all.visu.current_frame + pos, buf[0], g_all.champ[p].proces->color_rgb, 0);
			write_to_buffer(g_all.visu.current_frame + pos + 1, buf[1], g_all.champ[p].proces->color_rgb, 0);
			write_to_buffer(g_all.visu.current_frame + pos + 2, ' ', g_all.champ[p].proces->color_rgb, 0);
		}
		else
		{
			write_to_buffer(g_all.visu.current_frame + pos, '0', VM_COLOR, 0);
			write_to_buffer(g_all.visu.current_frame + pos + 1, '0', VM_COLOR, 0);
			write_to_buffer(g_all.visu.current_frame + pos + 2, ' ', VM_COLOR, 0);
		}
		if (p < (g_all.nb_champ - 1) && i + 1 == g_all.champ[p + 1].proces->pc)
			p++;
	}
	fill_current_frame();
	for (int j = 0; j < g_all.nb_champ; j++)
	{
		pos = jump_to_buf(g_all.champ[j].proces->pc);
		int tmp = g_all.visu.current_frame[pos].fore_color;
		g_all.visu.current_frame[pos].fore_color = g_all.visu.current_frame[pos].back_color;
		g_all.visu.current_frame[pos].back_color = tmp;
		pos++;
		tmp = g_all.visu.current_frame[pos].fore_color;
		g_all.visu.current_frame[pos].fore_color = g_all.visu.current_frame[pos].back_color;
		g_all.visu.current_frame[pos].back_color = tmp;
	}
	ft_memcpy(g_all.visu.current_frame_flame, g_all.visu.current_frame, g_all.visu.screen_size);
	for (int j = 0 ; j < g_all.visu.screen_size; j++)
	{
		if (g_all.visu.current_frame[j].to_print)
		{
			print_char(g_all.visu.current_frame[j], j);
		}
	}
	return (0);
}
