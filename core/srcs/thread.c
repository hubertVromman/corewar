/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:17:23 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/01 09:37:10 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		*sound_feu()
{
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	while (1)
	{
		system("afplay sound/feu.mp3 &");
		sleep(11);
	}
	pthread_exit(NULL);
}

void	*reader_func(void *rien)
{
	char			buf[2];
	int				res;
	struct termios	org_opts;
	rien = NULL;
	char	*s;

	// pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	res = tcgetattr(0, &org_opts);
	org_opts.c_lflag = ISIG & ~(ICANON);
	tcsetattr(0, TCSANOW, &org_opts);
	while (read(0, buf, 1))
	{
		if (buf[0] == ' ')
		{
			g_all.visu.pause = !g_all.visu.pause;
			if (g_all.visu.pause)
			{
				s = "Pause  ";
				system("pkill afplay");
			}
			else
				s = "Running";
			add_str_to_buffer(g_all.visu.next_frame + (g_all.visu.nb_cols * 5) + 5, s, WHITE, 0);
			insta_print_string(s, WHITE, 0, (g_all.visu.nb_cols * 5) + 5);
		}
		else if (buf[0] == 'q')
			g_all.visu.max_cps -= 10;
		else if (buf[0] == 'w')
			g_all.visu.max_cps--;
		else if (buf[0] == 'e')
			g_all.visu.max_cps++;
		else if (buf[0] == 'r')
			g_all.visu.max_cps += 10;
		else if (buf[0] == 'f')
		{
			g_all.visu.flame = !g_all.visu.flame;
			system("pkill afplay");
		}
		else if (buf[0] == '\e')
		{
			read(0, buf, 1);
			if (buf[0] == '[')
			{
				read(0, buf, 1);
				if (buf[0] == 'A')
				{
					g_all.visu.max_cps += 3;
					g_all.visu.mouse++;
				}
				else if (buf[0] == 'B')
				{
					g_all.visu.max_cps -= 3;
					g_all.visu.mouse--;
				}
			}
		}
		if (g_all.visu.max_cps <= 0)
			g_all.visu.max_cps = 1;
		if (g_all.visu.max_cps > 1000)
			g_all.visu.max_cps = 1000;
		g_all.visu.nb_frames_to_skip = g_all.visu.max_cps / 10 + 1;
	}
	return (NULL);
}

void	*th_feu()
{
	int width = g_all.visu.nb_cols;
	int height = FLAME_HEIGHT;
	int size = width * height;
	char *b;

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	b = g_all.visu.feu;
	char *ch = " .:^*xsS#$";
	int color;
	ft_bzero(g_all.visu.flame_buf, sizeof(t_printable) * FLAME_HEIGHT * width);
	for (int i = 0; i < width / 9; i++)
		b[rand() % width + width * (height - 1)] = 65;
	for (int i = 0; i < size; i++)
	{
		b[i]=(b[i]+b[i+1]+b[i+width]+b[i+width+1])/4;
		if (b[i] > 15)
			color = 0x000000ff;
		else if (b[i]>9)
			color = 0x00ffff00;
		else if (b[i]>4)
			color = 0x00ff0000;
		else
			color = 0;
		if (color != 0 && b[i] != 0)
			write_to_buf(g_all.visu.flame_buf + i, ch[(b[i]>9 ? 9 : b[i])], color, 0);
	}
	pthread_exit(NULL);
}

void	*th_calcul()
{
	int i;

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	if (!g_all.end)
	{
		display_ray();
		g_all.cycle++;
		return (0);
	}
	i = -1;
	ft_bzero(g_all.visu.next_frame, g_all.visu.screen_size * sizeof(t_printable));
	ft_memcpy(g_all.visu.next_frame + g_all.visu.offset_flame_y * g_all.visu.nb_cols, g_all.visu.current_frame + g_all.visu.offset_flame_y * g_all.visu.nb_cols, FLAME_HEIGHT * g_all.visu.nb_cols * sizeof(t_printable));
	while (++i < g_all.visu.nb_frames_to_skip && g_all.end)
	{
		g_all.cycle++;
		read_proces();
		g_all.ctd++;
		if (g_all.ctd == g_all.cycle_to_die)
		{
			g_all.ctd = 0;
			if ((g_all.end = reset_proc()) >= NBR_LIVE || g_all.check == MAX_CHECKS)
			{
				g_all.cycle_to_die -= CYCLE_DELTA;
				g_all.check = 0;
				if (g_all.cycle_to_die <= 0 || g_all.nb_proces_tot == 0)
				{
					g_all.end = 0;
				}
			}
			g_all.check++;
		}
	}
	print_vm_info();
	pthread_exit(NULL);
}
