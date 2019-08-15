/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:28:49 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/13 23:56:51 by sofchami         ###   ########.fr       */
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
			g_all.visu.flame = 1;
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
		// g_all.visu.nb_frames_to_skip = g_all.visu.max_cps / 100;
	}
	return (NULL);
}

int		display_start()
{
	int		i;

	if (g_all.flags[VISU])
	{
		ft_printf(HIDE_CURSOR SAVE_SCREEN "\e[H");
		dump_memory_colored();
		for (int j = 0; j < g_all.nb_champ; j++)
			increment_pc(g_all.champ[j].proces, 0);
		print_header();
		print_border();
		print_vm_info();
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

int		save_memory_colored()
{
	int		i;
	int		p;
	int		l;

	i = -1;
	p = 0;
	l = HEADER_HEIGHT;
	ft_printf("<b>");
	jump_to(2, HEADER_HEIGHT);
	while (++i < MEM_SIZE)
	{
		if (i >= g_all.champ[p].proces->pc && i < (g_all.champ[p].proces->pc + g_all.champ[p].exec_size))
			ft_printf(RGB_PRINT "%.2hhx", (g_all.champ[p].color_rgb >> 16) & 0xff, (g_all.champ[p].color_rgb >> 8) & 0xff, (g_all.champ[p].color_rgb >> 0) & 0xff, g_all.arena[i]);
		else
			ft_printf(RGB_PRINT "%.2hhx", 0x80, 0x80, 0x80, g_all.arena[i]);
		if (!((i + 1) % 64) && ++l)
			jump_to(2, l);
		else
			ft_printf(" ");
		if (p < (g_all.nb_champ - 1) && i + 1 == g_all.champ[p + 1].proces->pc)
			p++;
	}
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
	if (!(g_all.visu.current_frame = ft_memalloc(sizeof(t_printable) * g_all.visu.nb_cols * g_all.visu.nb_lines)))
		exit_func(MERROR, 0);
	if (!(g_all.visu.current_frame_flame = ft_memalloc(sizeof(t_printable) * g_all.visu.nb_cols * g_all.visu.nb_lines)))
		exit_func(MERROR, 0);
	if (!(g_all.visu.next_frame = ft_memalloc(sizeof(t_printable) * g_all.visu.nb_cols * g_all.visu.nb_lines)))
		exit_func(MERROR, 0);
	if (!(g_all.visu.feu = ft_memalloc(g_all.visu.nb_cols * FLAME_HEIGHT * 2)))
		exit_func(MERROR, 0);
	signal(SIGINT, exit_ctrl_c);
	pthread_create(&(g_all.visu.thread_reader), NULL, reader_func, NULL);
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
		g_all.champ[i].player_nb = 0 - g_all.champ[i].player_nb; // a changer
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

#include <limits.h>

int		main(int ac, char **av)
{
	// t_printable pr;
	// pr.back_color = 0x08888888 & 0x00ffffff;
	// ft_printf("%#.8x\n", pr.back_color);
	// ft_printf("%d\n", sizeof(t_printable));
	init_all(ac, av);
	display_start();
	beg_battle();
	exit_func(0, 0);
}
