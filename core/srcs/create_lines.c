/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:46:15 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/06 19:46:16 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_line(int *buffer, int x1, int y1)
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

static int	create_lines4(void)
{
	int		i;
	int		**lines;

	lines = g_all.end_screen.ray_lines;
	get_line(lines[15], g_all.end_screen.lumx, g_all.end_screen.lumy);
	get_line(lines[14], g_all.end_screen.luux, g_all.end_screen.luuy);
	i = -1;
	while (++i < g_all.end_screen.cy)
	{
		lines[14][i] = g_all.end_screen.cx - lines[14][i];
		lines[15][i] = g_all.end_screen.cx - lines[15][i];
	}
	i = -1;
	while (++i < g_all.end_screen.cy)
	{
		ft_swap(lines[14] + i, lines[15] + i);
	}
	i = -1;
	while (++i < g_all.end_screen.cy / 2)
	{
		ft_swap(lines[14] + i, lines[14] + g_all.end_screen.cy - 1 - i);
		ft_swap(lines[15] + i, lines[15] + g_all.end_screen.cy - 1 - i);
	}
	return (0);
}

static int	create_lines3(void)
{
	int		i;
	int		**lines;

	lines = g_all.end_screen.ray_lines;
	i = -1;
	while (++i < g_all.end_screen.cy)
	{
		lines[12][i] = g_all.end_screen.cx - lines[12][i];
		lines[13][i] = g_all.end_screen.cx - lines[13][i];
	}
	i = -1;
	while (++i < g_all.end_screen.cy)
	{
		ft_swap(lines[12] + i, lines[13] + i);
	}
	create_lines4();
	return (0);
}

static int	create_lines2(void)
{
	int		i;
	int		**lines;

	lines = g_all.end_screen.ray_lines;
	i = -1;
	while (++i < g_all.end_screen.cy / 2)
	{
		ft_swap(lines[4] + i, lines[4] + g_all.end_screen.cy - 1 - i);
		ft_swap(lines[5] + i, lines[5] + g_all.end_screen.cy - 1 - i);
	}
	get_line(lines[9], g_all.end_screen.brrx, g_all.end_screen.brry);
	get_line(lines[8], g_all.end_screen.brmx, g_all.end_screen.brmy);
	get_line(lines[11], g_all.end_screen.blmx, g_all.end_screen.blmy);
	get_line(lines[10], g_all.end_screen.bllx, g_all.end_screen.blly);
	i = -1;
	while (++i < g_all.end_screen.cy / 2)
	{
		ft_swap(lines[10] + i, lines[10] + g_all.end_screen.cy - 1 - i);
		ft_swap(lines[11] + i, lines[11] + g_all.end_screen.cy - 1 - i);
	}
	get_line(lines[12], g_all.end_screen.lbbx, g_all.end_screen.lbby);
	get_line(lines[13], g_all.end_screen.lbmx, g_all.end_screen.lbmy);
	create_lines3();
	return (0);
}

int			create_lines(void)
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
	i = -1;
	while (++i < g_all.end_screen.cy / 2)
	{
		ft_swap(lines[2] + i, lines[2] + g_all.end_screen.cy - 1 - i);
		ft_swap(lines[3] + i, lines[3] + g_all.end_screen.cy - 1 - i);
	}
	get_line(lines[4], g_all.end_screen.ruux, g_all.end_screen.ruuy);
	get_line(lines[5], g_all.end_screen.rumx, g_all.end_screen.rumy);
	get_line(lines[7], g_all.end_screen.rbmx, g_all.end_screen.rbmy);
	get_line(lines[6], g_all.end_screen.rbbx, g_all.end_screen.rbby);
	create_lines2();
	return (0);
}
