/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:28:49 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/11 17:47:16 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		read_file(t_champ *champ)
{
	int ret;
	int fd;

	if ((fd = open(champ->file_name, O_RDONLY)) == -1)
		return (error_func(champ, OPEN_FAIL) - 2);
	champ->file_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (!(champ->file = malloc(champ->file_size + 1)))
		exit_func(-2, 0);
	ret = read(fd, champ->file, champ->file_size);
	champ->file[champ->file_size] = 0;
	close(fd);
	return (ret < 0 ? -1 : 0);
}

int		get_prog_size(char *file_content)
{
	int		size;

	ft_memcpy(&size, file_content + 4 + PROG_NAME_LENGTH + 4, 4);
	return (change_endianness(size));
}

int		get_file(char *file_name, t_champ *new)
{
	int		ret;

	new->file_name = file_name;
	if (ft_strcmp(get_ext(file_name), "cor"))
		return (error_func(new, NOT_COR_FILE) - 2);
	if ((ret = read_file(new)) < 0)
		return (ret);
	if (new->file_size < g_all.header_size)
		return (-1);
	new->exec_size = get_prog_size(new->file);
	if (new->file_size != new->exec_size + g_all.header_size)
		return (-1);
	if (new->exec_size > CHAMP_MAX_SIZE)
		return (error_func(new, TOO_LARGE) - 2);
	new->exec_file = new->file + g_all.header_size;
	return (0);
}

int		get_champ(char *file_name)
{
	int		ret;
	int		i;
	int		j;

	if ((ret = get_file(file_name, &(g_all.champ[g_all.nb_champ]))) == -1)
		error_func(&(g_all.champ[g_all.nb_champ]), READ_ERROR);
	if (ret < 0 && !(g_all.flags[0]))
		exit_func(-1, 0);
	i = g_all.next_champ_nb ? g_all.next_champ_nb - 1 : 0;
	while (++i && (j = -1))
	{
		while (++j < g_all.nb_champ)
		{
			if (i == g_all.champ[j].player_nb)
				break;
		}
		if (j == g_all.nb_champ)
		{
			g_all.champ[g_all.nb_champ].player_nb = i;
			break;
		}
	}
	g_all.next_champ_nb = 0;
	return (0);
}

t_proces	*init_proces(int pc, t_proces *parent, int player_nb)
{
	t_proces *proc;
	proc = ft_memalloc(sizeof(t_proces));
	proc->pc = pc;
	if (parent)
	{
		ft_memcpy(proc->reg, parent->reg, REG_NUMBER * 4);
	}
	else
	{
		proc->reg[0] = player_nb;
	}
	return(proc);
}

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
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", g_all.champ[i].player_nb, g_all.champ[i].exec_size, g_all.champ[i].file + 4, g_all.champ[i].file + PROG_NAME_LENGTH + 12);
		}
	}
	return (0);
}

int		init_all(int ac, char **av)
{
	int i;

	i = -1;
	ft_bzero(&g_all, sizeof(g_all));
	if (!(g_all.flags = ft_memalloc(sizeof(OP))))
		exit_func(-2, 0);
	g_all.header_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	g_all.cycle_to_die = CYCLE_TO_DIE;
	parse_arg(ac, av);
	if (g_all.nb_champ < 1)
		exit_func(-1, 1);
	g_all.nbr_processes = g_all.nb_champ;
	g_all.pos_depart = MEM_SIZE / g_all.nb_champ;
	while (++i < g_all.nb_champ)
	{
		ft_memcpy(g_all.arena + (g_all.pos_depart * i),
			g_all.champ[i].exec_file, g_all.champ[i].file_size - g_all.header_size);
		g_all.champ[i].proces = init_proces(g_all.pos_depart * i, NULL, g_all.champ[i].player_nb);
	}
	return (0);
}

int		main(int ac, char **av)
{
	init_all(ac, av);
	display_start();
	int d= 2;
	t_arg *c = get_arguments(&d);
	ft_printf("%p\n", c);
	for (int i=0;i<4;i++)
		ft_printf("%d %d %x\n", c[i].size, c[i].type, c[i].value);
	exit_func(0, 0);
}
