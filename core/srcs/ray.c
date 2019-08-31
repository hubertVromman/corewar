/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:28:59 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/31 07:38:57 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_line(int *buffer, int x1, int y1)
{
	int		i;
	int		x2;
	int		y2;
	float	f;
	float	j;

	x2 = g_all.end_screen.cx;
	y2 = g_all.end_screen.cy;
	i = -1;
	while (++i < g_all.end_screen.cy)
		buffer[i] = ft_max(x1, x2);
	if (y1 > y2)
		ft_swap(&y1, &y2);
	if (x1 > x2)
		ft_swap(&x1, &x2);
	f = (float)(x2 - x1) / (y2 - y1);
	j = x1;
	i = -1;
	while (++i < y2 - y1)
	{
		buffer[i] = (int)j;
		j += f;
	}
	return (0);
}

int		create_lines(void)
{
	int		i;
	int		**lines;

	lines = g_all.end_screen.ray_lines;
	i = -1;
	while (++i < 16)
		if (!(lines[i] = malloc(sizeof(int) * g_all.end_screen.cy)))
			exit_func(MERROR, 0);
	get_line(lines[0], g_all.end_screen.ullx, g_all.end_screen.ully);
	get_line(lines[1], g_all.end_screen.ulmx, g_all.end_screen.ulmy);
	get_line(lines[2], g_all.end_screen.urmx, g_all.end_screen.urmy);
	get_line(lines[3], g_all.end_screen.urrx, g_all.end_screen.urry);
	for (int j = 0; j < g_all.end_screen.cy / 2; j++)
	{
		ft_swap(lines[2] + j, lines[2] + g_all.end_screen.cy - 1 - j);
		ft_swap(lines[3] + j, lines[3] + g_all.end_screen.cy - 1 - j);
	}
	get_line(lines[4], g_all.end_screen.ruux, g_all.end_screen.ruuy);
	get_line(lines[5], g_all.end_screen.rumx, g_all.end_screen.rumy);
	for (int j = 0; j < g_all.end_screen.cy / 2; j++)
	{
		ft_swap(lines[4] + j, lines[4] + g_all.end_screen.cy - 1 - j);
		ft_swap(lines[5] + j, lines[5] + g_all.end_screen.cy - 1 - j);
	}
	get_line(lines[7], g_all.end_screen.rbmx, g_all.end_screen.rbmy);
	get_line(lines[6], g_all.end_screen.rbbx, g_all.end_screen.rbby);
	get_line(lines[9], g_all.end_screen.brrx, g_all.end_screen.brry);
	get_line(lines[8], g_all.end_screen.brmx, g_all.end_screen.brmy);
	get_line(lines[11], g_all.end_screen.blmx, g_all.end_screen.blmy);
	get_line(lines[10], g_all.end_screen.bllx, g_all.end_screen.blly);
	for (int j = 0; j < g_all.end_screen.cy / 2; j++)
	{
		ft_swap(lines[10] + j, lines[10] + g_all.end_screen.cy - 1 - j);
		ft_swap(lines[11] + j, lines[11] + g_all.end_screen.cy - 1 - j);
	}
	get_line(lines[12], g_all.end_screen.lbbx, g_all.end_screen.lbby);
	get_line(lines[13], g_all.end_screen.lbmx, g_all.end_screen.lbmy);
	for (int j = 0; j < g_all.end_screen.cy; j++)
	{
		lines[12][j] = g_all.end_screen.cx - lines[12][j];
		lines[13][j] = g_all.end_screen.cx - lines[13][j];
	}
	for (int j = 0; j < g_all.end_screen.cy; j++)
	{
		ft_swap(lines[12] + j, lines[13] + j);
	}
	get_line(lines[15], g_all.end_screen.lumx, g_all.end_screen.lumy);
	get_line(lines[14], g_all.end_screen.luux, g_all.end_screen.luuy);
	for (int j = 0; j < g_all.end_screen.cy; j++)
	{
		lines[14][j] = g_all.end_screen.cx - lines[14][j];
		lines[15][j] = g_all.end_screen.cx - lines[15][j];
	}
	for (int j = 0; j < g_all.end_screen.cy; j++)
	{
		ft_swap(lines[14] + j, lines[15] + j);
	}
	for (int j = 0; j < g_all.end_screen.cy / 2; j++)
	{
		ft_swap(lines[14] + j, lines[14] + g_all.end_screen.cy - 1 - j);
		ft_swap(lines[15] + j, lines[15] + g_all.end_screen.cy - 1 - j);
	}
	return (0);
}

int		display_winner(void)
{
	int		len_player;
	int		pos_x;
	int		pos_y;
	int		color;

	len_player = ft_strlen(g_all.champ[g_all.player_last_live].player_name);
	pos_x = rand() % (g_all.visu.nb_cols - len_player);
	pos_y = rand() % (g_all.visu.nb_lines - 1);
	color = rand() % 0xffffff;
	add_str_to_buffer(g_all.visu.flame_buf + pos_y * g_all.visu.nb_cols + pos_x + (len_player - 8) / 2, "WINNER :", color, 0);
	add_str_to_buffer(g_all.visu.flame_buf + (pos_y + 1) * g_all.visu.nb_cols + pos_x, g_all.champ[g_all.player_last_live].player_name, color, 0);
	return (0);
}

int		print_ray(int *first_column, int *second_column, int w, int i)
{
	int		pos;
	int		color;

	w = 0;
	color = rand() % 0xffffff;
	for (int j = 0; j < g_all.end_screen.cy; j++)
	{
		pos = first_column[j] + (j + (i >= 3 && i <= 6 ? g_all.end_screen.cy : 0)) * g_all.visu.nb_cols;
		for (int k = 0; k < second_column[j] - first_column[j]; k++)
		{
			write_to_buf(g_all.visu.flame_buf + pos++, ' ', 0, color);
		}
	}
	return (0);
}

int		display_ray(void)
{
	ft_memcpy(g_all.visu.flame_buf, g_all.visu.current_frame, sizeof(t_printable) * g_all.visu.screen_size);
	for (int i = 0; i < 8; i++)
	{
		print_ray(g_all.end_screen.ray_lines[i * 2], g_all.end_screen.ray_lines[i * 2 + 1], g_all.cycle, i);
	}
	display_winner();
	usleep(600 * 1000);
	return (0);
}
