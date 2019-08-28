/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 00:08:03 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/29 00:08:05 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		fill_border(void)
{
	int			i;
	int			wd;
	t_printable	*buf;

	i = -1;
	buf = g_all.visu.current_frame;
	wd = g_all.visu.nb_cols;
	while (++i < SCREEN_HEIGHT)
	{
		write_to_buf(buf + wd * (i + 1) - 1, ' ', 0, BORDER_COLOR);
		write_to_buf(buf + wd * (i + 1) - 2, ' ', 0, BORDER_COLOR);
		(i >= HEADER_HEIGHT - 2)
	&& (write_to_buf(buf + wd * (i + 1) - INFO_WIDTH, ' ', 0, BORDER_COLOR)
	|| write_to_buf(buf + wd * (i + 1) - INFO_WIDTH - 1, ' ', 0, BORDER_COLOR));
		write_to_buf(buf + wd * i, ' ', 0, BORDER_COLOR);
		write_to_buf(buf + wd * i + 1, ' ', 0, BORDER_COLOR);
	}
	i = -1;
	while (++i < wd)
	{
		write_to_buf(buf + 0 * wd + i, ' ', 0, BORDER_COLOR);
		write_to_buf(buf + 8 * wd + i, ' ', 0, BORDER_COLOR);
		write_to_buf(buf + SCREEN_HEIGHT * wd + i, ' ', 0, BORDER_COLOR);
	}
	return (0);
}

int		fill_header(void)
{
	t_printable	*st_point;

	st_point = g_all.visu.current_frame + g_all.visu.nb_cols / 2 - 21;
	add_str_to_buffer(st_point + 1 * g_all.visu.nb_cols,
		"   _____                                  ", COREWAR_COLOR, 0);
	add_str_to_buffer(st_point + 2 * g_all.visu.nb_cols,
		"  / ____|                                 ", COREWAR_COLOR, 0);
	add_str_to_buffer(st_point + 3 * g_all.visu.nb_cols,
		" | |     ___  _ __ _____      ____ _ _ __ ", COREWAR_COLOR, 0);
	add_str_to_buffer(st_point + 4 * g_all.visu.nb_cols,
		" | |    / _ \\| '__/ _ \\ \\ /\\ / / _` | '__|", COREWAR_COLOR, 0);
	add_str_to_buffer(st_point + 5 * g_all.visu.nb_cols,
		" | |___| (_) | | |  __/\\ V  V / (_| | |   ", COREWAR_COLOR, 0);
	add_str_to_buffer(st_point + 6 * g_all.visu.nb_cols,
		"  \\_____\\___/|_|  \\___| \\_/\\_/ \\__,_|_|   ", COREWAR_COLOR, 0);
	return (0);
}

int		fill_memory(void)
{
	int		i;
	int		p;
	char	*buf;

	i = -1;
	p = 0;
	buf = NULL;
	while (++i < MEM_SIZE)
	{
		if (i == g_all.champ[p].proces->pc)
		{
			while (i < g_all.champ[p].proces->pc + g_all.champ[p].exec_size)
			{
				if (ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[i], &buf) == -1)
					exit_func(MERROR, 0);
				add_str_to_buffer(g_all.visu.current_frame +
					jump_to_buf(i++), buf, g_all.champ[p].proces->color_rgb, 0);
				free(buf);
			}
			p < g_all.nb_champ - 1 && p++;
		}
		add_str_to_buffer(g_all.visu.current_frame +
			jump_to_buf(i), "00", VM_COLOR, 0);
	}
	return (0);
}

int		fill_player_info(void)
{
	char		*tmp;
	int			i;
	t_printable	*st_point;

	i = -1;
	while (++i < g_all.nb_champ)
	{
		st_point = g_all.visu.current_frame + (HEADER_HEIGHT + i % 2 * 5)
		* g_all.visu.nb_cols + g_all.visu.nb_cols - INFO_WIDTH + 3 + i / 2 * 51;
		if (ft_printf("PLAYER %3d : %c%s%#>", g_all.champ[i].player_nb, 0,
			g_all.champ[i].player_name, &tmp) == -1)
			exit_func(MERROR, 0);
		add_str_to_buffer(st_point + 8 * g_all.visu.nb_cols, tmp, WHITE, 0);
		add_name_to_buffer(st_point + 8 * g_all.visu.nb_cols + 13,
			tmp + 14, g_all.champ[i].color_rgb, 0);
		free(tmp);
		add_str_to_buffer(st_point + 9 * g_all.visu.nb_cols + 5,
			"Last live", WHITE, 0);
		add_str_to_buffer(st_point + 10 * g_all.visu.nb_cols + 5,
			"Lives period", WHITE, 0);
		add_str_to_buffer(st_point + 11 * g_all.visu.nb_cols + 5,
			"Nbr of process", WHITE, 0);
	}
	return (0);
}

int		fill_process_info(void)
{
	char		*tmp;
	t_printable	*st_point;
	int			width;

	width = g_all.visu.nb_cols;
	st_point = g_all.visu.current_frame + HEADER_HEIGHT * width
		+ width - INFO_WIDTH + 3;
	tmp = NULL;
	if (ft_printf("%1$/43c Info %1$/43c %#>", '-', &tmp) == -1)
		exit_func(MERROR, 0);
	add_str_to_buffer(st_point, tmp, WHITE, 0);
	free(tmp);
	add_str_to_buffer(st_point + 1 * width, "Cycles              :", WHITE, 0);
	add_str_to_buffer(st_point + 2 * width, "Cycles/second limit :", WHITE, 0);
	add_str_to_buffer(st_point + 3 * width, "Nbr of process      :", WHITE, 0);
	add_str_to_buffer(st_point + 4 * width, "Lives period        :", WHITE, 0);
	add_str_to_buffer(st_point + 5 * width, "Cycle to die        :", WHITE, 0);
	add_str_to_buffer(st_point + 6 * width, "Aff :", WHITE, 0);
	if (ft_printf("%1$/40c ALL proces %1$/40c %#>", '-', &tmp) == -1)
		exit_func(MERROR, 0);
	add_str_to_buffer(st_point + 18 * width, tmp, WHITE, 0);
	free(tmp);
	return (0);
}
