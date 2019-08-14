/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lecteur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:57:39 by sofchami          #+#    #+#             */
/*   Updated: 2019/08/14 06:32:44 by sofchami         ###   ########.fr       */
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
	jump_to(X, 2 + HEADER_HEIGHT);
	ft_printf("Cycles/second limit : %4d", g_all.visu.max_cps);
	return (0);
}

char *avant_feu(int *si)
{
	int		i;
	int		l;

	char *s = NULL;
	int s_size = 0;
	char *buffer;
	int siz;

	i = 3583;
	l = HEADER_HEIGHT + 56;
	// ft_printf("<b>");
	siz = ft_printf("\e[%d;%dH  %#>", HEADER_HEIGHT + 56 + 1, 0 + 1, &buffer);
	s = realloc(s, s_size + siz);
	ft_memcpy(s + s_size, buffer, siz);
				free(buffer);
	s_size += siz;
	while (++i < MEM_SIZE)
	{
		siz = ft_printf(RGB_PRINT "%.2hhx%#>", (g_all.color[i] >> 16) & 0xff, (g_all.color[i] >> 8) & 0xff, (g_all.color[i] >> 0) & 0xff, g_all.arena[i], &buffer);
		s = realloc(s, s_size + siz);
		ft_memcpy(s + s_size, buffer, siz);
				free(buffer);
		s_size += siz;
		if (!((i + 1) % 64) && ++l)
		{
			// jump_to(0, l);
			siz = ft_printf("\e[%d;%dH %#>", l + 1, 1, &buffer);
			s = realloc(s, s_size + siz);
			ft_memcpy(s + s_size, buffer, siz);
				free(buffer);
			s_size += siz;
		}
		siz = ft_printf(" %#>", &buffer);
			s = realloc(s, s_size + siz);
			ft_memcpy(s + s_size, buffer, siz);
				free(buffer);
			s_size += siz;
	}
	// ft_printf("</>");
	*si = s_size;
	return s;
}

int feu(char *s, int s_size)
{
	int width = g_all.visu.nb_cols;
	int height = g_all.visu.nb_lines;
	int size = width * height;
	char *b;
	static int sofiane = 1;
	if (sofiane == 1)
		g_all.visu.feu = ft_memalloc(size * 2 + 1);
	b = g_all.visu.feu;
	char *ch = " .:^*xsS#$";
	int color;

	int siz;
	// ft_printf("\e[%d;%dH", height - 18, width);
	for (int i = 0; i < width/9; i++)
		b[rand() % width + width * (height-1)]=65;
	for (int i = 0; i < size; i++)
	{
		b[i]=(b[i]+b[i+1]+b[i+width]+b[i+width+1])/4;
		if (b[i] > 15)
			color=4;
		else if (b[i]>9)
			color = 3;
		else if (b[i]>4)
			color = 1;
		else
			color = 0;
		if(i<size && i > size - 17 * width)
		{
			char *buffer;
			siz = 0;
			if (color != 0 && b[i] != 0)
				siz = ft_printf("\e[%d;%dH\e[%dm%c%#>", i/width,i%width,30 + color, ch[(b[i]>9 ? 9 : b[i])], &buffer);
			else if (i%width > 193 || i/width > 74)
				siz = ft_printf("\e[%d;%dH\e[%dm%c%#>", i/width,i%width,30 + color, ' ', &buffer);
			if (siz)
			{
				s = realloc(s, s_size + siz);
				ft_memcpy(s + s_size, buffer, siz);
				s_size += siz;
				free(buffer);
			}
		}
	}
	write(1, s, s_size);
	sofiane--;
	return 9;
}

void	*test_thread()
{
	g_all.flamme = avant_feu(&g_all.size_flamme);
	feu(g_all.flamme, g_all.size_flamme);
	pthread_exit(NULL);
}

int		do_visu_stuff()
{
	int		i;
	int		sleep_time;
	int		current_cps;
	pthread_t check;

	current_cps = g_all.visu.max_cps;
	update_cps();
	i = 0;
	sleep_time = 1000 / g_all.visu.max_cps;
	while (i < sleep_time)
	{
		i += 10;
		usleep(10 * 1000);
		if (current_cps != g_all.visu.max_cps)
		{
			update_cps();
			current_cps = g_all.visu.max_cps;
			i = 0;
		}
	}
	if (g_all.visu.pause)
	{
		return (1);
	}
	else
	{
		if (g_all.visu.flame)
		{
			if (!g_all.thread)
				pthread_create(&g_all.thread_id, NULL, sound_feu, NULL);
			g_all.thread = 1;;
			// int size;
			// char *s = avant_feu(&size);
			// g_all.flamme = avant_feu(&g_all.size_flamme);
			pthread_create(&check, NULL, test_thread, NULL);
			// feu(s, size);
			pthread_join(check, NULL);
		}
		g_all.visu.skipped_frames = 0;
		return (0);
	}
}

int		beg_battle()
{
	int end;
	int i;
	int check;

	end = 1;
	i = -1;
	check = 0;
	while (end)
	{
		if (g_all.flags[VISU] && do_visu_stuff())
			continue;
		g_all.cycle++;
		read_proces();
		g_all.ctd++;
		if (g_all.ctd == g_all.cycle_to_die)
		{
			g_all.ctd = 0;
			if ((end = reset_proc()) >= NBR_LIVE || check == MAX_CHECKS)
			{
				g_all.cycle_to_die -= CYCLE_DELTA;
				check = 0;
				if (g_all.cycle_to_die <= 0 || g_all.nb_proces_tot == 0)
				{
					end = 0;
				}
			}
			check++;
		}
		if (g_all.flags[VISU])print_vm_info();
	}
	if (!g_all.flags[VISU])ft_printf("Contestant %d, \"%s\", has won !\n", g_all.champ[g_all.player_last_live].player_nb, g_all.champ[g_all.player_last_live].player_name);
	else while(1);
	return (0);
}
