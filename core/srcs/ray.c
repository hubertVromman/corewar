/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:28:59 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/28 01:29:01 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_line(int *buffer, int x1, int y1)
{
	int		dx;
	int		dy;
	float	f;
	float	j;
	int		x2;
	int		y2;

	x2 = g_all.end_screen.cx;
	y2 = g_all.end_screen.cy;
	for (int i = 0; i < g_all.end_screen.cy; i++)
		buffer[i] = ft_max(x1, x2);

	if (y1 > y2)
		ft_swap(&y1, &y2);

	if (x1 > x2)
		ft_swap(&x1, &x2);

	dx = x2 - x1;
	dy = y2 - y1;

	f = (float) dx / dy;
	j = x1;
	for (int i = 0; i < dy; i++)
	{
		buffer[i] = (int) j;
		j += f;
	}
	return (0);
}

int 	display_winner()
{
	int len_player;

	len_player = ft_strlen(g_all.champ[g_all.player_last_live].player_name);
	system("clear");
	jump_to((g_all.visu.nb_cols - 7) / 2, g_all.visu.nb_lines / 4);
	ft_printf(BOLD_WHITE "WINNER :\n");
	jump_to((g_all.visu.nb_cols - len_player) / 2 ,(g_all.visu.nb_lines / 4) + 1);
	ft_printf(BOLD_WHITE "%s\n", g_all.champ[g_all.player_last_live].player_name);
	return (0);
}

int		display_ray()
{
	display_winner();
	for (int w = 0; ; w++)
	{
		get_line(g_all.end_screen.first_column, g_all.end_screen.ullx, g_all.end_screen.ully);
		get_line(g_all.end_screen.second_column, g_all.end_screen.ulmx, g_all.end_screen.ulmy);
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			jump_to(g_all.end_screen.first_column[j], j);
			for (int k = 0; k < g_all.end_screen.second_column[j] - g_all.end_screen.first_column[j]; k++)
			{
				ft_printf(COLOR_PRINT " ", 41 + w % 4);
			}
		}
		get_line(g_all.end_screen.first_column, g_all.end_screen.urmx, g_all.end_screen.urmy);
		get_line(g_all.end_screen.second_column, g_all.end_screen.urrx, g_all.end_screen.urry);
		for (int j = 0; j < g_all.end_screen.cy / 2; j++)
		{
			ft_swap(g_all.end_screen.first_column + j, g_all.end_screen.first_column + g_all.end_screen.cy - 1 - j);
			ft_swap(g_all.end_screen.second_column + j, g_all.end_screen.second_column + g_all.end_screen.cy - 1 - j);
		}
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			jump_to(g_all.end_screen.first_column[j], j);
			for (int k = 0; k < g_all.end_screen.second_column[j] - g_all.end_screen.first_column[j]; k++)
			{
				ft_printf(COLOR_PRINT " ", 41 + (w + 1) % 4);
			}
		}
		get_line(g_all.end_screen.first_column, g_all.end_screen.ruux, g_all.end_screen.ruuy);
		get_line(g_all.end_screen.second_column, g_all.end_screen.rumx, g_all.end_screen.rumy);
		for (int j = 0; j < g_all.end_screen.cy / 2; j++)
		{
			ft_swap(g_all.end_screen.first_column + j, g_all.end_screen.first_column + g_all.end_screen.cy - 1 - j);
			ft_swap(g_all.end_screen.second_column + j, g_all.end_screen.second_column + g_all.end_screen.cy - 1 - j);
		}
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			jump_to(g_all.end_screen.first_column[j], j);
			for (int k = 0; k < g_all.end_screen.second_column[j] - g_all.end_screen.first_column[j]; k++)
			{
				ft_printf(COLOR_PRINT " ", 41 + (w + 2) % 4);
			}
		}
		get_line(g_all.end_screen.second_column, g_all.end_screen.rbmx, g_all.end_screen.rbmy);
		get_line(g_all.end_screen.first_column, g_all.end_screen.rbbx, g_all.end_screen.rbby);
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			jump_to(g_all.end_screen.first_column[j], j + g_all.end_screen.cy);
			for (int k = 0; k < g_all.end_screen.second_column[j] - g_all.end_screen.first_column[j]; k++)
			{
				ft_printf(COLOR_PRINT " ", 41 + (w + 3) % 4);
			}
		}

		get_line(g_all.end_screen.second_column, g_all.end_screen.brrx, g_all.end_screen.brry);
		get_line(g_all.end_screen.first_column, g_all.end_screen.brmx, g_all.end_screen.brmy);
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			jump_to(g_all.end_screen.first_column[j], j + g_all.end_screen.cy);
			for (int k = 0; k < g_all.end_screen.second_column[j] - g_all.end_screen.first_column[j]; k++)
			{
				ft_printf(COLOR_PRINT " ", 41 + w % 4);
			}
		}
		get_line(g_all.end_screen.second_column, g_all.end_screen.blmx, g_all.end_screen.blmy);
		get_line(g_all.end_screen.first_column, g_all.end_screen.bllx, g_all.end_screen.blly);
		for (int j = 0; j < g_all.end_screen.cy / 2; j++)
		{
			ft_swap(g_all.end_screen.first_column + j, g_all.end_screen.first_column + g_all.end_screen.cy - 1 - j);
			ft_swap(g_all.end_screen.second_column + j, g_all.end_screen.second_column + g_all.end_screen.cy - 1 - j);
		}
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			jump_to(g_all.end_screen.first_column[j], j + g_all.end_screen.cy);
			for (int k = 0; k < g_all.end_screen.second_column[j] - g_all.end_screen.first_column[j]; k++)
			{
				ft_printf(COLOR_PRINT " ", 41 + (w + 1) % 4);
			}
		}
		get_line(g_all.end_screen.first_column, g_all.end_screen.lbbx, g_all.end_screen.lbby);
		get_line(g_all.end_screen.second_column, g_all.end_screen.lbmx, g_all.end_screen.lbmy);
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			g_all.end_screen.first_column[j] = g_all.end_screen.cx - g_all.end_screen.first_column[j];
			g_all.end_screen.second_column[j] = g_all.end_screen.cx - g_all.end_screen.second_column[j];
		}
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			ft_swap(g_all.end_screen.first_column + j, g_all.end_screen.second_column + j);
			// ft_swap(g_all.end_screen.second_column + j, g_all.end_screen.second_column + g_all.end_screen.cy - 1 - j);
		}
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			jump_to(g_all.end_screen.first_column[j], j + g_all.end_screen.cy);
			for (int k = 0; k < g_all.end_screen.second_column[j] - g_all.end_screen.first_column[j]; k++)
			{
				ft_printf(COLOR_PRINT " ", 41 + (w + 2) % 4);
			}
		}
		get_line(g_all.end_screen.second_column, g_all.end_screen.lumx, g_all.end_screen.lumy);
		get_line(g_all.end_screen.first_column, g_all.end_screen.luux, g_all.end_screen.luuy);
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			g_all.end_screen.first_column[j] = g_all.end_screen.cx - g_all.end_screen.first_column[j];
			g_all.end_screen.second_column[j] = g_all.end_screen.cx - g_all.end_screen.second_column[j];
		}
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			ft_swap(g_all.end_screen.first_column + j, g_all.end_screen.second_column + j);
			// ft_swap(g_all.end_screen.second_column + j, g_all.end_screen.second_column + g_all.end_screen.cy - 1 - j);
		}
		for (int j = 0; j < g_all.end_screen.cy / 2; j++)
		{
			ft_swap(g_all.end_screen.first_column + j, g_all.end_screen.first_column + g_all.end_screen.cy - 1 - j);
			ft_swap(g_all.end_screen.second_column + j, g_all.end_screen.second_column + g_all.end_screen.cy - 1 - j);
		}
		for (int j = 0; j < g_all.end_screen.cy; j++)
		{
			jump_to(g_all.end_screen.first_column[j], j);
			for (int k = 0; k < g_all.end_screen.second_column[j] - g_all.end_screen.first_column[j]; k++)
			{
				ft_printf(COLOR_PRINT " ", 41 + (w + 3) % 4);

			}
		}
		usleep(300 * 1000);
	}
	return (0);
}
