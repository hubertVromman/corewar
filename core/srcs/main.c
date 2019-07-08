/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:28:49 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/06 14:28:52 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_flags(int ac, char **av)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "--"))
			return (i + 1);
		if (av[i][0] == '-')
		{
			j = 0;
			while (av[i][++j])
			{
				if ((k = ft_indexof(OP, av[i][j])) == -1)
					exit_func(-1, 1);
				g_all.flags[k] = 1;
			}
		}
		else
			return (i);
	}
	return (i);
}

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
		return (error_func(new, NOT_COR_FILE));
	if ((ret = read_file(new)) < 0)
		return (ret);
	if (new->file_size < g_all.header_size)
		return (-1);
	new->exec_size = get_prog_size(new->file);
	if (new->file_size != new->exec_size + g_all.header_size)
		return (-1);
	if (new->exec_size > CHAMP_MAX_SIZE)
		return (error_func(new, TOO_LARGE) - 2);
	return (0);
}

int		get_champ(char **av)
{
	int		ret;
	int		i;
	int		j;

	i = -1;
	j = g_all.start;
	while (++i < g_all.nb_champ)
	{
		if ((ret = get_file(av[j], &(g_all.champ[i]))) == -1)
			error_func(&(g_all.champ[i]), READ_ERROR);
		if (ret < 0 && !(g_all.flags[0]))
			exit_func(-1, 0);
		++j;
	}
	return (0);
}

int		init_all(int ac, char **av)
{
	ft_bzero(&g_all, sizeof(g_all));
	if (!(g_all.flags = ft_memalloc(sizeof(OP))))
		exit_func(-2, 0);
	g_all.start = get_flags(ac, av);
	g_all.nb_champ = ac - g_all.start;
	if (g_all.nb_champ < 1)
		exit_func(-1, 1);
	if (!(g_all.champ = ft_memalloc(sizeof(t_champ) * g_all.nb_champ)))
		exit_func(MERROR, 0);
	g_all.header_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	return (0);
}

int		main(int ac, char **av)
{
	init_all(ac, av);
	get_champ(av);
	for (int i = 0; i < g_all.nb_champ; ++i)
	{
		ft_printf("%d\n\n", g_all.champ[i].exec_size);
		for (size_t j = 0; j < g_all.champ[i].file_size; ++j)
		{
			ft_printf("%4d ", g_all.champ[i].file[j]);
			if (!((j+1)%16))
				ft_printf("\n");
		}
		ft_printf("\n\n");
	}
	exit_func(0, 0);
}
