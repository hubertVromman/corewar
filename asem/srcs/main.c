/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:30:00 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/06 14:30:04 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_flags(int ac, char **av, t_a *all)
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
				all->flags[k] = 1;
			}
		}
		else
			return (i);
	}
	return (i);
}

int		create_file(t_a *all, char *file_name)
{
	all->file->s_name = file_name;
	if (ft_strcmp(get_ext(all->file->s_name), "s"))
		return (error_func(all->file, NOT_S_FILE));
	if (read_file(all->file) == -1)
		return (-1);
	if (create_header(all, all->file) == -1)
		return (-1);
	if (create_code(all, all->file) == -1)
		return (-1);
	return (write_file(all, all->file, get_cor_name(file_name)));
}

int		create_files(int ac, char **av, t_a *all)
{
	int		i;

	if (ac < 2)
		exit_func(-1, 1);
	i = get_flags(ac, av, all) - 1;
	while (++i < ac)
	{
		all->nb_files_created += create_file(all, av[i]) + 1;
		all->nb_errors += all->file->nb_error;
		free_file(all->file);
		ft_bzero(all->file, sizeof(t_file));
		if (!all->flags[0])
			break ;
	}
	return (0);
}

int		instantiate_all(t_file *file)
{
	ft_bzero(file, sizeof(t_file));
	ft_bzero(&g_all, sizeof(t_a));
	g_all.header_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	g_all.file = file;
	if (!(g_all.flags = malloc(sizeof(OP))))
		exit_func(-2, 0);
	return (0);
}

int		main(int ac, char **av)
{
	t_file	file;

	instantiate_all(&file);
	create_files(ac, av, &g_all);
	exit_func(0, 0);
}
