/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:28:49 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/20 17:27:16 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		parse_arg(int ac, char **av)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (!ft_strcmp(av[i] + 1, "n"))
			{
				if (i + 1 == ac)
					exit_func(-1, 1);
				g_all.n_option = 1;
				g_all.next_champ_nb = ft_atoi(av[++i]);
			}
			else if (!ft_strcmp(av[i] + 1, "dump"))
			{
				if (i + 1 == ac || g_all.dump_period)
					exit_func(-1, 1);
				g_all.dump_period = ft_atoi(av[++i]);
				if (g_all.dump_period < 1)
					exit_func(-1, 1);
			}
			else
			{
				j = 0;
				while (av[i][++j])
				{
					if ((k = ft_indexof(OP, av[i][j])) == -1)
						exit_func(-1, 1);
					g_all.flags[k] = 1;
				}
			}
		}
		else
		{
			get_champ(av[i]);
			g_all.nb_champ++;
		}
	}
	return (0);
}

int		print_debug_info()
{
	int		i;
	int		j;

	ft_printf("%1$/30c DEBUG %1$/30c\n", '-');
	ft_printf("cycle count : %d\n", g_all.cycle);
	ft_printf("%/*c\n", 67, '-');
	i = -1;
	while (++i < g_all.nb_champ)
	{
		j = -1;
		ft_printf("%d\n", g_all.champ[i].nb_proces);
		while (++j < g_all.champ[i].nb_proces)
		{
			ft_printf("player_nb %2d | proces_id %2d | pc %4d | opcode " CHAR_HEX_PRINT " | cycle_left %4d\n", g_all.champ[i].player_nb, j, g_all.champ[i].proces[j].pc, g_all.champ[i].proces[j].opcode, g_all.champ[i].proces[j].cycle_left);
		}
		if (i != g_all.nb_champ - 1)
			ft_printf("%/*c\n", 67, '-');
	}
	ft_printf("%/*c\n", 67, '-');
	return (0);
}

void	*reader_func(void *rien)
{
	char			buf[2];
	int				res;
	struct termios	org_opts;
	rien = NULL;

	res = tcgetattr(0, &org_opts);
	org_opts.c_lflag = ISIG & ~(ICANON);
	tcsetattr(0, TCSANOW, &org_opts);
	while (read(0, buf, 1))
	{
		if (buf[0] == ' ')
			g_all.visu.pause = !g_all.visu.pause;
		else if (buf[0] == 'q')
			g_all.visu.max_cps -= 10;
		else if (buf[0] == 'w')
			g_all.visu.max_cps--;
		else if (buf[0] == 'e')
			g_all.visu.max_cps++;
		else if (buf[0] == 'r')
			g_all.visu.max_cps += 10;
		else if (buf[0] == 'f')
			g_all.visu.flame = !g_all.visu.flame;
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

int		get_line(int *buffer, int x1, int y1)
{
	int		dx;
	int		dy;
	float	f;
	float	j;
	int		x2;
	int		y2;

	int		sign;

	x2 = g_all.end_screen.cx;
	y2 = g_all.end_screen.cy;
	for (int i = 0; i < g_all.end_screen.cy; i++)
		buffer[i] = ft_max(x1, x2);
	sign = 1; // a quoi sert la variable ca ne change jamais nan ?

	if (y1 > y2)
		ft_swap(&y1, &y2);

	if (x1 > x2)
		ft_swap(&x1, &x2);

	dx = x2 - x1;
	dy = y2 - y1;

	f = (float) dx / dy;
	j = sign == -1 ? x2 : x1;
	for (int i = 0; i < dy; i++)
	{
		buffer[i] = (int) j;
		j += f * sign;
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

int		display_start()
{
	int		i;

	if (g_all.flags[VISU])
	{
		ft_printf(HIDE_CURSOR SAVE_SCREEN "\e[H");
		init_current_frame();
		// display_ray();
		// jump_to(g_all.end_screen.ulmx, g_all.end_screen.ulmy);
		// ft_printf(RGB_PRINT_BG " ", 255, 0, 0);
	}
	else
	{
		ft_printf("%s\n", "Introducing contestants...");
		i = -1;
		while (++i < g_all.nb_champ)
		{
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", g_all.champ[i].player_nb, g_all.champ[i].exec_size, g_all.champ[i].player_name, g_all.champ[i].comment);
		}
	}
	return (0);
}

int		init_func_pointer()
{
	g_all.func[0] = &operation_live;
	g_all.func[1] = &operation_ld;
	g_all.func[2] = &operation_st;
	g_all.func[3] = &operation_add;
	g_all.func[4] = &operation_sub;
	g_all.func[5] = &operation_and;
	g_all.func[6] = &operation_or;
	g_all.func[7] = &operation_xor;
	g_all.func[8] = &operation_zjmp;
	g_all.func[9] = &operation_ldi;
	g_all.func[10] = &operation_sti;
	g_all.func[11] = &operation_fork;
	g_all.func[12] = &operation_lld;
	g_all.func[13] = &operation_lldi;
	g_all.func[14] = &operation_lfork;
	g_all.func[15] = &operation_aff;
	return (0);
}

int		sort_champs()
{
	int		i;
	t_champ	tmp;

	i = -1;
	while (++i < g_all.nb_champ - 1)
	{
		if (g_all.champ[i].player_nb > g_all.champ[i + 1].player_nb)
		{
			ft_memcpy(&tmp, &g_all.champ[i], sizeof(t_champ));
			ft_memcpy(&g_all.champ[i], &g_all.champ[i + 1], sizeof(t_champ));
			ft_memcpy(&g_all.champ[i + 1], &tmp, sizeof(t_champ));
			i = -1;
		}
	}
	return (0);
}

int		init_end_screen()
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
	g_all.end_screen.cx = g_all.visu.nb_cols / 2;
	g_all.end_screen.cy = g_all.visu.nb_lines / 2;
	if (!(g_all.end_screen.first_column = malloc(sizeof(int) * g_all.visu.nb_lines / 2)))
		exit_func(MERROR, 0);
	if (!(g_all.end_screen.second_column = malloc(sizeof(int) * g_all.visu.nb_lines / 2)))
		exit_func(MERROR, 0);
	return (0);
}

int		init_visu()
{
	int		i;
	int		j;
	struct ttysize	ts;

	srand(time(NULL));
	ioctl(0, TIOCGSIZE, &ts);
	g_all.visu.nb_cols = ts.ts_cols;
	g_all.visu.nb_lines = ts.ts_lines;
	g_all.visu.screen_size = g_all.visu.nb_lines * g_all.visu.nb_cols;
	ft_memset(g_all.color, 0x80, sizeof(g_all.color));
	g_all.visu.offset_flame_y = g_all.visu.nb_lines - 18;
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
	g_all.visu.pause = 1;
	g_all.visu.max_cps = 50;
	if (!(g_all.visu.flame_buf = malloc(sizeof(t_printable) * g_all.visu.nb_cols * FLAME_HEIGHT)))
		exit_func(MERROR, 0);
	if (!(g_all.visu.current_frame = ft_memalloc(sizeof(t_printable) * g_all.visu.screen_size)))
		exit_func(MERROR, 0);
	if (!(g_all.visu.current_frame_flame = ft_memalloc(sizeof(t_printable) * g_all.visu.screen_size)))
		exit_func(MERROR, 0);
	if (!(g_all.visu.next_frame = malloc(sizeof(t_printable) * g_all.visu.screen_size)))
		exit_func(MERROR, 0);
	if (!(g_all.visu.feu = malloc(g_all.visu.nb_cols * FLAME_HEIGHT * 2)))
		exit_func(MERROR, 0);
	for (int l = 0; l < g_all.visu.screen_size; l++)
	{
		g_all.visu.current_frame[l].to_print = ' ';
		g_all.visu.current_frame_flame[l].to_print = ' ';
	}
	signal(SIGINT, exit_ctrl_c);
	pthread_create(&(g_all.visu.thread_reader), NULL, reader_func, NULL);
	init_end_screen();
	return (0);
}

int		init_all(int ac, char **av)
{
	int i;

	i = -1;
	ft_bzero(&g_all, sizeof(g_all));
	g_all.header_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	g_all.cycle_to_die = CYCLE_TO_DIE;
	parse_arg(ac, av);
	if (g_all.nb_champ < 1 || g_all.nb_champ > 4)
		exit_func(-1, 1);
	g_all.pos_depart = MEM_SIZE / g_all.nb_champ;
	sort_champs();
	if (g_all.flags[VISU])
		init_visu();
	while (++i < g_all.nb_champ)
	{
		if (!g_all.n_option)
			g_all.champ[i].player_nb = 0 - g_all.champ[i].player_nb;
		ft_memcpy(g_all.arena + (g_all.pos_depart * i),
			g_all.champ[i].exec_file, g_all.champ[i].exec_size);
		create_proces(g_all.pos_depart * i, NULL, &(g_all.champ[i])); //gestion d'erreur
		g_all.champ[i].proces[0].opcode = g_all.arena[g_all.champ[i].proces->pc];
		g_all.champ[i].proces[0].cycle_left = get_cycle_left(g_all.champ[i].proces->opcode);
	}
	init_func_pointer();
	return (0);
}

void		*sound_feu()
{
	while (1)
	{
		system("afplay sound/feu.mp3 &");
		sleep(11);
	}
	pthread_exit(NULL);
}

int		main(int ac, char **av)
{
	init_all(ac, av);
	display_start();
	ft_printf("%d\n", g_all.dump_period);
	beg_battle();
	exit_func(0, 0);
}
