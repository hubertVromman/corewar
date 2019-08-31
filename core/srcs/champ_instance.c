/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_instance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 14:00:06 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/31 04:03:35 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		get_prog_size(char *file_content)
{
	int		size;

	ft_memcpy(&size, file_content + 4 + PROG_NAME_LENGTH + 4, 4);
	return (change_endianness(size));
}

static int		read_file(t_champ *champ)
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

static int		get_file(char *file_name, t_champ *new)
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

int				get_champ(char *file_name)
{
	int		ret;
	int		i;
	int		j;
	t_champ	*current;

	current = &(g_all.champ[g_all.nb_champ]);
	if ((ret = get_file(file_name, current)) == -1)
		error_func(current, READ_ERROR);
	if (ret < 0 && !(g_all.flags[FORCE_LAUNCH]))
		exit_func(-1, 0);
	i = g_all.next_champ_nb ? g_all.next_champ_nb - 1 : 0;
	if (i >= 1000)
		i = 0;
	while (++i && (j = -1))
	{
		if (i >= 1000)
			i = 1;
		while (++j < g_all.nb_champ)
		{
			if (i == g_all.champ[j].player_nb)
				break ;
		}
		if (j == g_all.nb_champ)
		{
			g_all.champ[g_all.nb_champ].player_nb = i;
			break ;
		}
	}
	current->player_name = current->file + 4;
	current->comment = current->file + PROG_NAME_LENGTH + 12;
	g_all.next_champ_nb = 0;
	return (0);
}
