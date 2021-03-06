/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:24:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/28 01:24:33 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	init_end_screen2(void)
{
	g_all.end_screen.brrx = g_all.visu.nb_cols * 3 / 4 + SIZE_ANIM_X;
	g_all.end_screen.brry = g_all.visu.nb_lines;
	g_all.end_screen.brmx = g_all.visu.nb_cols * 3 / 4 - SIZE_ANIM_X;
	g_all.end_screen.brmy = g_all.visu.nb_lines;
	g_all.end_screen.blmx = g_all.visu.nb_cols / 4 + SIZE_ANIM_X;
	g_all.end_screen.blmy = g_all.visu.nb_lines;
	g_all.end_screen.bllx = g_all.visu.nb_cols / 4 - SIZE_ANIM_X;
	g_all.end_screen.blly = g_all.visu.nb_lines;
	g_all.end_screen.lbbx = 0;
	g_all.end_screen.lbby = g_all.visu.nb_lines * 3 / 4 + SIZE_ANIM_Y;
	g_all.end_screen.lbmx = 0;
	g_all.end_screen.lbmy = g_all.visu.nb_lines * 3 / 4 - SIZE_ANIM_Y;
	g_all.end_screen.lumx = 0;
	g_all.end_screen.lumy = g_all.visu.nb_lines / 4 + SIZE_ANIM_Y;
	g_all.end_screen.luux = 0;
	g_all.end_screen.luuy = g_all.visu.nb_lines / 4 - SIZE_ANIM_Y;
	return (0);
}

static int	init_end_screen(void)
{
	g_all.end_screen.ullx = g_all.visu.nb_cols / 4 - SIZE_ANIM_X;
	g_all.end_screen.ully = 0;
	g_all.end_screen.ulmx = g_all.visu.nb_cols / 4 + SIZE_ANIM_X;
	g_all.end_screen.ulmy = 0;
	g_all.end_screen.urmx = g_all.visu.nb_cols * 3 / 4 - SIZE_ANIM_X;
	g_all.end_screen.urmy = 0;
	g_all.end_screen.urrx = g_all.visu.nb_cols * 3 / 4 + SIZE_ANIM_X;
	g_all.end_screen.urry = 0;
	g_all.end_screen.ruux = g_all.visu.nb_cols;
	g_all.end_screen.ruuy = g_all.visu.nb_lines / 4 - SIZE_ANIM_Y;
	g_all.end_screen.rumx = g_all.visu.nb_cols;
	g_all.end_screen.rumy = g_all.visu.nb_lines / 4 + SIZE_ANIM_Y;
	g_all.end_screen.rbmx = g_all.visu.nb_cols;
	g_all.end_screen.rbmy = g_all.visu.nb_lines * 3 / 4 - SIZE_ANIM_Y;
	g_all.end_screen.rbbx = g_all.visu.nb_cols;
	g_all.end_screen.rbby = g_all.visu.nb_lines * 3 / 4 + SIZE_ANIM_Y;
	init_end_screen2();
	g_all.end_screen.cx = g_all.visu.nb_cols / 2;
	g_all.end_screen.cy = g_all.visu.nb_lines / 2;
	create_lines();
	return (0);
}

static int	init_visu2(void)
{
	int		i;
	size_t	super_screen;

	srand(time(NULL));
	g_all.visu.pause = 1;
	g_all.visu.max_cps = 50;
	g_all.visu.offset_flame_y = g_all.visu.nb_lines - 18;
	g_all.visu.screen_size = g_all.visu.nb_lines * g_all.visu.nb_cols;
	super_screen = sizeof(t_printable) * g_all.visu.screen_size;
	if (!(g_all.visu.flame_buf = malloc(super_screen))
		|| !(g_all.visu.current_frame = malloc(super_screen))
		|| !(g_all.visu.current_frame_flame = malloc(super_screen))
		|| !(g_all.visu.next_frame = malloc(super_screen))
		|| !(g_all.visu.feu = malloc(g_all.visu.screen_size)))
		exit_func(MERROR, 0);
	i = -1;
	while (++i < g_all.visu.screen_size)
		g_all.visu.current_frame[i].to_print = ' ';
	g_all.visu.previous_pos = -1;
	signal(SIGINT, exit_ctrl_c);
	pthread_create(&(g_all.visu.thread_reader), NULL, reader_func, NULL);
	init_end_screen();
	return (0);
}

int			init_visu(void)
{
	int				i;
	int				j;
	struct ttysize	ts;

	ioctl(0, TIOCGSIZE, &ts);
	g_all.visu.nb_cols = ts.ts_cols;
	g_all.visu.nb_lines = ts.ts_lines;
	ft_memset(g_all.color, 0x80, sizeof(g_all.color));
	i = -1;
	while (++i < g_all.nb_champ)
	{
		if (i == 0)
			g_all.champ[i].color_rgb = P1_COLOR;
		else if (i == 1)
			g_all.champ[i].color_rgb = P2_COLOR;
		else if (i == 2)
			g_all.champ[i].color_rgb = P3_COLOR;
		else if (i == 3)
			g_all.champ[i].color_rgb = P4_COLOR;
		j = -1;
		while (++j < g_all.champ[i].exec_size)
			g_all.color[(g_all.pos_depart * i) + j] = g_all.champ[i].color_rgb;
	}
	init_visu2();
	return (0);
}
