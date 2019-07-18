/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:28:49 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/18 02:24:07 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		read_arena_op(int pc)
{
	int opcode;

	opcode = 0;
	opcode = g_all.arena[pc];
	if (opcode < 1 || opcode > 16)
		return (0);
	return (opcode);
}

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
				ft_printf("ici\n");
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

// int		reset_proc()
// {
// 	int i;
// 	int total_lives;
// 	t_proces *tmp;

// 	i = -1;
// 	total_lives = 0;
// 	while (++i < g_all.nb_champ)
// 	{
// 		tmp = g_all.champ[i].proces;
// 		while (tmp)
// 		{
// 			if (!tmp->lives_period)
// 				tmp->dead = 1;
// 			else
// 			{
// 				total_lives += tmp->lives_period;
// 				tmp->lives_period = 0;
// 			}
// 			tmp = tmp->next;
// 		}
// 	}
// 	return (total_lives);
// }

// int		beg_battle()
// {
// 	int end;
// 	int i;
// 	int check;

// 	end = 0;
// 	i = -1;
// 	check = 0;
// 	while (!end)
// 	{
// 		//read_proces
// 		//operations
// 		if (!(g_all.cycle_to_die % g_all.cycle)) // ??
// 		{
// 			check++;
// 			if ((reset_proc() < NBR_LIVE) || (check == MAX_CHECKS))
// 			{
// 				g_all.cycle_to_die -= CYCLE_DELTA;
// 				check = 0;
// 				if (g_all.cycle_to_die <= 0)
// 				{
// 					end = 1;
// 				}
// 			}
// 		}
// 		g_all.cycle++;
// 	}
// 	return (0);
// }

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
		while (++j < g_all.champ[i].nb_proces)
		{
			ft_printf("player_nb %2d | proces_id %2d | pc %4d | opcode %.2hhx | cycle_left %4d\n", g_all.champ[i].player_nb, j, g_all.champ[i].proces[0].pc, g_all.champ[i].proces[0].opcode, g_all.champ[i].proces[0].cycle_left);
		}
		if (i != g_all.nb_champ - 1)
			ft_printf("%/*c\n", 67, '-');
	}
	ft_printf("%/*c\n", 67, '-');
	return (0);
}

int		display_start()
{
	int		i;

	if (g_all.flags[1])
		dump_memory_colored();
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

int		init_all(int ac, char **av)
{
	int i;

	i = -1;
	ft_printf("t_a %d t_champ %d\n", sizeof(t_a), sizeof(t_champ));
	ft_bzero(&g_all, sizeof(g_all));
	g_all.header_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	g_all.cycle_to_die = CYCLE_TO_DIE;
	parse_arg(ac, av);
	if (g_all.nb_champ < 1)
		exit_func(-1, 1);
	g_all.nb_proces_tot = g_all.nb_champ;
	g_all.pos_depart = MEM_SIZE / g_all.nb_champ;
	while (++i < g_all.nb_champ)
	{
		ft_memcpy(g_all.arena + (g_all.pos_depart * i),
			g_all.champ[i].exec_file, g_all.champ[i].exec_size);
		create_proces(g_all.pos_depart * i, NULL, &(g_all.champ[i])); //gestion d'erreur
		g_all.champ[i].proces[0].opcode = g_all.arena[g_all.champ[i].proces->pc];
		g_all.champ[i].proces[0].cycle_left = get_cycle_left(g_all.champ[i].proces->opcode);
	}
	return (0);
}

int		main(int ac, char **av)
{
	init_all(ac, av);
	display_start();
	print_debug_info();
	dump_memory_colored();
	exit_func(0, 0);
}
