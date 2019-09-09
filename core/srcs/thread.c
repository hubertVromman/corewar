/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:17:23 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/04 18:30:00 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	*sound_feu(void)
{
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	while (1)
	{
		system("afplay sound/feu.mp3 &");
		sleep(11);
	}
	pthread_exit(NULL);
}

int		handle_char(char buf)
{
	if (buf == ' ')
	{
		g_all.visu.pause = !g_all.visu.pause;
		g_all.pause_changed = 1;
		if (g_all.visu.pause)
			kill_feu();
	}
	else if (buf == 'q')
		g_all.visu.max_cps -= 10;
	else if (buf == 'w')
		g_all.visu.max_cps--;
	else if (buf == 'e')
		g_all.visu.max_cps++;
	else if (buf == 'r')
		g_all.visu.max_cps += 10;
	else if (buf == 'm')
		g_all.visu.max_cps = 1000;
	else if (buf == 'f')
	{
		g_all.visu.flame = !g_all.visu.flame;
		if (!g_all.visu.flame)
			kill_feu();
	}
	return (0);
}

void	*reader_func(void)
{
	char			buf;
	int				res;
	struct termios	org_opts;

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	res = tcgetattr(0, &org_opts);
	org_opts.c_lflag = ISIG & ~(ICANON);
	tcsetattr(0, TCSANOW, &org_opts);
	while (read(0, &buf, 1))
	{
		handle_char(buf);
		if (g_all.visu.max_cps <= 0)
			g_all.visu.max_cps = 1;
		if (g_all.visu.max_cps > 1000)
			g_all.visu.max_cps = 1000;
		g_all.visu.nb_frames_to_skip = g_all.visu.max_cps / 10 + 1;
	}
	pthread_exit(NULL);
}

void	*th_feu(void)
{
	int		width;
	int		size;
	char	*b;
	int		color;
	int		i;

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	width = g_all.visu.nb_cols;
	size = width * FLAME_HEIGHT;
	b = g_all.visu.feu;
	ft_bzero(g_all.visu.flame_buf, sizeof(t_printable) * FLAME_HEIGHT * width);
	i = -1;
	while (++i < width / 9)
		b[rand() % width + width * (FLAME_HEIGHT - 1)] = 65;
	i = -1;
	while (++i < size)
	{
		b[i] = (b[i] + b[i + 1] + b[i + width] + b[i + width + 1]) / 4;
		if ((b[i] > 15 && (color = 0x0000ff))
			|| (b[i] > 9 && (color = 0xffff00))
			|| (b[i] > 4 && (color = 0xff0000)))
			write_to_buf(g_all.visu.flame_buf + i,
				" .:^*xsS#$"[(b[i] > 9 ? 9 : b[i])], color, 0);
	}
	pthread_exit(NULL);
}

void	*th_calcul(void)
{
	int		i;
	int		offset;

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	if (g_all.end)
	{
		display_ray();
		g_all.cycle++;
		return (0);
	}
	i = -1;
	ft_bzero(g_all.visu.next_frame,
		g_all.visu.screen_size * sizeof(t_printable));
	offset = g_all.visu.offset_flame_y * g_all.visu.nb_cols;
	ft_memcpy(
		g_all.visu.next_frame + offset,
		g_all.visu.current_frame + offset,
		FLAME_HEIGHT * g_all.visu.nb_cols * sizeof(t_printable));
	while (++i < g_all.visu.nb_frames_to_skip && !g_all.end)
	{
		single_cycle();
	}
	print_vm_info();
	pthread_exit(NULL);
}
