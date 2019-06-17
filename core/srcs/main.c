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

#include <stdio.h>
int		read_file(t_champ *champ)
{
	int ret;
	int fd;

	if ((fd = open(champ->file_name, O_RDONLY)) == -1)
		return (error_func(champ, OPEN_FAIL));
	champ->file_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (!(champ->file = malloc(champ->file_size + 1)))
		exit_func(-2, 0);
	ret = read(fd, champ->file, champ->file_size);
	champ->file[champ->file_size] = 0;
	close(fd);
	return (ret < 0 ? -1 : 0);
}

int		get_file(char *file_name, t_champ *new)
{
	new->file_name = file_name;
	if (ft_strcmp(get_ext(file_name), "cor"))
		return (error_func(new, NOT_COR_FILE));
	if (read_file(new) == -1)
		return (-1);
	return (0);
}

int		get_champ(char **av)
{
	int		i;

	i = -1;
	while (++i < g_all.nb_champ)
	{
		get_file(av[i + 1], &(g_all.champ[i]));
	}
	return (0);
}

int		init_all(nb_champ)
{
	ft_bzero(&g_all, sizeof(g_all));
	if (nb_champ < 1)
		exit_func(-1, 1);
	g_all.nb_champ = nb_champ;
	if (!(g_all.champ = ft_memalloc(sizeof(t_champ) * nb_champ)))
		exit_func(MERROR, 0);
	if (!(g_all.flags = ft_memalloc(sizeof(OP))))
		exit_func(-2, 0);
	return (0);
}

int		main(int ac, char **av)
{
	init_all(ac - 1);
	get_champ(av);
	for (int i = 0; i < g_all.nb_champ; ++i)
	{
		for (size_t j = 0; j < g_all.champ->file_size; ++j)
		{
			ft_printf("%4d ", g_all.champ->file[j]);
			if (!((j+1)%16))
				ft_printf("\n");
		}
		ft_printf("\n\n");
	}
	exit_func(0, 0);
}
