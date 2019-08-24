/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lecteur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:57:39 by sofchami          #+#    #+#             */
/*   Updated: 2019/08/20 23:55:07 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		read_arena_op(int pc)
{
	int		opcode;

	opcode = g_all.arena[pc];
	if (opcode < 1 || opcode > 16)
		return (0);
	return (opcode);
}

int		reset_proc()
{
	int i;
	int total_lives_period;
	int k;

	i = -1;
	total_lives_period = 0;
	while (++i < g_all.nb_champ)
	{
		k = -1;
		while (++k < g_all.champ[i].nb_proces)
		{
			if (!g_all.champ[i].proces[k].lives_period)
			{
				detele_proces(&g_all.champ[i], k);
				k--;
			}
			else
			{
				total_lives_period += g_all.champ[i].proces[k].lives_period;
				g_all.champ[i].proces[k].lives_period = 0;
			}
		}
		g_all.champ[i].lives_period = 0;
	}
	return (total_lives_period);
}

int		do_actions(int i, int k)
{
	int l;
	t_arg *arg;

	l = 0;
	arg = get_arguments(&g_all.champ[i].proces[k]);
	if (arg && (g_all.champ[i].proces[k].opcode > 0 && g_all.champ[i].proces[k].opcode < 17 ) && g_all.func[g_all.champ[i].proces[k].opcode - 1](&g_all.champ[i], &g_all.champ[i].proces[k], arg) != 0)
	{
		increment_pc(&g_all.champ[i].proces[k], g_all.champ[i].proces[k].opcode == ZJMP_OP ? 0 : arg[0].size + arg[1].size + arg[2].size + arg[3].size + g_op_tab[g_all.champ[i].proces[k].opcode - 1].codage + 1);
		g_all.queu[l] = &g_all.champ[i].proces[k];
		l++;
	}
	else
	{
		if (g_all.champ[i].proces[k].opcode > 1 && g_all.champ[i].proces[k].opcode < 16)
			increment_pc(&g_all.champ[i].proces[k], g_op_tab[g_all.champ[i].proces[k].opcode - 1].nb_params + 2);
		else
			increment_pc(&g_all.champ[i].proces[k], 1);
	}
	return (l);
}

int		read_opcode(int l)
{
	int i;

	i = -1;
	while (++i < l)
	{
		g_all.queu[i]->opcode = read_arena_op(g_all.queu[i]->pc);
		g_all.queu[i]->cycle_left = get_cycle_left(g_all.queu[i]->opcode);
	}
	return (0);
}

int		read_proces()
{
	int i;
	int k;
	int		l;

	ft_bzero(&g_all.queu, sizeof(g_all.queu));
	i = g_all.nb_champ;
	l = 0;
	while (i--)
	{
		k = g_all.champ[i].nb_proces;
		while (k--)
		{
			if (g_all.champ[i].proces[k].cycle_left)
			{
				g_all.champ[i].proces[k].cycle_left--;
				if (!g_all.champ[i].proces[k].cycle_left)
				{
					l = do_actions(i, k);
				}
			}
			else // utilité de ce else ? normalement il devrait pas rentrer dedans...
			{
				g_all.champ[i].proces[k].opcode = read_arena_op(g_all.champ[i].proces[k].pc);
				g_all.champ[i].proces[k].cycle_left = get_cycle_left(g_all.champ[i].proces[k].opcode);
			}
		}
	}
	read_opcode(l);
	// if (!g_all.flags[VISU]) print_debug_info();
	return (0);
}

int		update_cps()
{
	jump_to(X + 20, 2 + HEADER_HEIGHT);
	ft_printf(": %4d", g_all.visu.max_cps);
	return (0);
}

void	*th_feu()
{
	int width = g_all.visu.nb_cols;
	int height = FLAME_HEIGHT;
	int size = width * height;
	char *b;

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
			write_to_buffer(g_all.visu.flame_buf + i, ch[(b[i]>9 ? 9 : b[i])], color, 0);
	}
	pthread_exit(NULL);
}

void	*th_calcul()
{
	int i;

	ft_bzero(g_all.visu.next_frame, g_all.visu.screen_size * sizeof(t_printable));
	ft_memcpy(g_all.visu.next_frame + g_all.visu.offset_flame_y * g_all.visu.nb_cols, g_all.visu.current_frame + g_all.visu.offset_flame_y * g_all.visu.nb_cols, FLAME_HEIGHT * g_all.visu.nb_cols * sizeof(t_printable));
	i = -1;
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
	pthread_exit(NULL);
}

int		print_char(t_printable printable, int pos)
{
	// static int previous_bg = 0;
	// static int previous_fg = 0;
	// static int previous_pos = -1;

	// if (previous_pos + 1 != pos)
	// {
		jump_to(pos % g_all.visu.nb_cols, pos / g_all.visu.nb_cols);
	// 	previous_pos = pos;
	// }
	// else
	// 	previous_pos++;
	// if (previous_bg != printable.back_color)
	// {
		ft_printf(RGB_PRINT_BG, (printable.back_color >> 16) & 0xff, (printable.back_color >> 8) & 0xff, (printable.back_color >> 0) & 0xff);
	// 	previous_bg = printable.back_color;
	// }
	// if (previous_fg != printable.fore_color)
	// {
		ft_printf(RGB_PRINT, (printable.fore_color >> 16) & 0xff, (printable.fore_color >> 8) & 0xff, (printable.fore_color >> 0) & 0xff);
	// 	previous_fg = printable.fore_color;
	// }
	ft_printf("%c", printable.to_print);
	return (0);
}

int		copy_and_print_buffer(t_printable *dst, t_printable *src, int size)
{
	for (int l = 0; l < size; l++)
	{
		if (src[l].to_print && ft_memcmp(src + l, dst + l, sizeof(t_printable)))
		{
			ft_memcpy(dst + l, src + l, sizeof(t_printable));
			print_char(dst[l], l);
		}
	}
	return (0);
}

int		do_visu_stuff()
{
	int			i;
	int			sleep_time;
	static int	current_cps = 0;
	int			has_frame;

	i = 0;
	has_frame = 0;
	if (!g_all.visu.pause)
	{
		has_frame = 1;
		pthread_create(&g_all.visu.thread_calcul, NULL, th_calcul, NULL);
		if (g_all.visu.flame)
			pthread_create(&g_all.visu.thread_flamme, NULL, th_feu, NULL);
	}
	sleep_time = 1000 / g_all.visu.max_cps;
	while (i < sleep_time)
	{
		i += 10;
		if (current_cps != g_all.visu.max_cps)
		{
			update_cps();
			current_cps = g_all.visu.max_cps;
			sleep_time = 1000 / g_all.visu.max_cps;
			i = 0;
		}
		usleep(10 * 1000);
	}
	pthread_join(g_all.visu.thread_calcul, NULL);
	pthread_join(g_all.visu.thread_flamme, NULL);
	if (has_frame)
	{
		for (int l = 0; l < g_all.visu.screen_size; l++)
		{
			if (g_all.visu.next_frame[l].to_print && ft_memcmp(g_all.visu.next_frame + l, g_all.visu.current_frame + l, sizeof(t_printable)))
			{
				ft_memcpy(g_all.visu.current_frame + l, g_all.visu.next_frame + l, sizeof(t_printable));
			}
		}
		if (g_all.visu.flame)
			for (int l = 0; l < FLAME_HEIGHT * g_all.visu.nb_cols; l++)
			{
				if (g_all.visu.flame_buf[l].to_print)
					ft_memcpy(g_all.visu.next_frame + g_all.visu.offset_flame_y * g_all.visu.nb_cols + l, g_all.visu.flame_buf + l, sizeof(t_printable));
				if (!(g_all.visu.next_frame[g_all.visu.offset_flame_y * g_all.visu.nb_cols + l].to_print))
					g_all.visu.next_frame[g_all.visu.offset_flame_y * g_all.visu.nb_cols + l].to_print = ' ';
			}
		copy_and_print_buffer(g_all.visu.current_frame_flame, g_all.visu.next_frame, g_all.visu.screen_size);
	}
	if (g_all.visu.flame)
	{
		if (!g_all.visu.thread_sound)
			pthread_create(&g_all.visu.thread_sound, NULL, sound_feu, NULL);
	}
	return (0);
}

int		beg_battle()
{
	g_all.visu.nb_frames_to_skip = 10;
	g_all.end = 1;
	while (g_all.end)
	{
		if (g_all.flags[VISU])
				do_visu_stuff();
		else
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
		// if (g_all.flags[VISU])print_vm_info();
	}
	if (!g_all.flags[VISU])ft_printf("Contestant %d, \"%s\", has won !\n", g_all.champ[g_all.player_last_live].player_nb, g_all.champ[g_all.player_last_live].player_name);
	else {ft_printf("fin\n");while(1);}
	return (0);
}
