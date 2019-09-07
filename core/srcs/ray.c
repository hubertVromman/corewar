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

static int	display_winner(void)
{
	int		len_player;
	int		pos_x;
	int		pos_y;
	int		color;

	len_player = ft_strlen(g_all.champ[g_all.player_last_live].player_name);
	pos_x = rand() % (g_all.visu.nb_cols - len_player);
	pos_y = rand() % (g_all.visu.nb_lines - 1);
	color = rand() % WHITE;
	add_str_to_buf(g_all.visu.flame_buf + pos_y * g_all.visu.nb_cols + pos_x +
		(len_player - 8) / 2, "WINNER :", color, 0);
	add_str_to_buf(g_all.visu.flame_buf + (pos_y + 1) * g_all.visu.nb_cols +
		pos_x, g_all.champ[g_all.player_last_live].player_name, color, 0);
	return (0);
}

static int	print_ray(int *first_column, int *second_column, int ray_idx)
{
	int		pos;
	int		color;
	int		i;
	int		j;

	color = rand() % WHITE;
	i = -1;
	while (++i < g_all.end_screen.cy)
	{
		pos = first_column[i] + (i + (ray_idx >= 3 && ray_idx <= 6 ?
			g_all.end_screen.cy : 0)) * g_all.visu.nb_cols;
		j = -1;
		while (++j < second_column[i] - first_column[i])
		{
			write_to_buf(g_all.visu.flame_buf + pos++, ' ', 0, color);
		}
	}
	return (0);
}

int			display_ray(void)
{
	int		i;

	pthread_cancel(g_all.visu.thread_reader);
	ft_memcpy(g_all.visu.current_frame_flame, g_all.visu.current_frame,
		sizeof(t_printable) * g_all.visu.screen_size);
	ft_bzero(g_all.visu.flame_buf, sizeof(t_printable) *
		g_all.visu.screen_size);
	i = -1;
	while (++i < 8)
	{
		print_ray(g_all.end_screen.ray_lines[i * 2],
			g_all.end_screen.ray_lines[i * 2 + 1], i);
	}
	display_winner();
	usleep(600 * 1000);
	return (0);
}
