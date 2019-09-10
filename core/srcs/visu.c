/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:38:07 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/10 05:45:33 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		jump_to(int x, int y)
{
	ft_printf("\e[%d;%dH", y + 1, x + 1);
	return (0);
}

void	exit_ctrl_c(int c)
{
	usleep(50 * 1000);
	c = 0;
	exit_func(0, 0);
}

int		jump_to_buf(int pc)
{
	int		offset_x;
	int		offset_y;
	int		pos;

	offset_x = MEMORY_OFFSET_X;
	offset_y = HEADER_HEIGHT;
	pc = calc_pc(pc);
	pos = g_all.visu.nb_cols * (offset_y + pc / 64) + offset_x + pc % 64 * 3;
	return (pos);
}

int		kill_feu(void)
{
	pthread_cancel(g_all.visu.thread_sound);
	system("pkill afplay");
	g_all.visu.thread_sound = 0;
	return (0);
}

int		do_visu_stuff(void)
{
	int			has_frame;

	has_frame = 1;
	update_cps();
	if (g_all.end)
		pthread_create(&g_all.visu.thread_calcul, NULL, th_calcul, NULL);
	else if (!g_all.visu.pause)
	{
		pthread_create(&g_all.visu.thread_calcul, NULL, th_calcul, NULL);
		if (g_all.visu.flame)
			pthread_create(&g_all.visu.thread_flamme, NULL, th_feu, NULL);
	}
	else if (!g_all.cycle)
		print_vm_info();
	else
		has_frame = 0;
	usleep(1000 * 1000 / g_all.visu.max_cps);
	pthread_join(g_all.visu.thread_calcul, NULL);
	pthread_join(g_all.visu.thread_flamme, NULL);
	if (has_frame)
		print_frame_diff();
	if (!g_all.visu.pause && g_all.visu.flame && !g_all.visu.thread_sound
		&& !g_all.flags[SILENCE])
		pthread_create(&g_all.visu.thread_sound, NULL, sound_feu, NULL);
	return (0);
}
