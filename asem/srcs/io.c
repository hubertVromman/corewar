/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:56:57 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/12 16:56:58 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		read_file(t_file *file)
{
	int ret;
	int fd;

	if ((fd = open(file->s_name, O_RDONLY)) == -1)
		return (error_func(file, OPEN_FAIL));
	file->file_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (!(file->s_file_content = malloc(file->file_size + 1)))
		exit_func(-2, 0);
	ret = read(fd, file->s_file_content, file->file_size);
	file->s_file_content[file->file_size] = 0;
	close(fd);
	return (ret < 0 ? -1 : 0);
}

int		write_file(t_a *all, t_file *file, char *file_name)
{
	int fd;

	file->cor_name = file_name;
	if (!file_name || file->nb_error)
		return (-1);
	if ((fd = open(file_name,
		O_WRONLY | O_CREAT | O_TRUNC, 0755)) == -1)
		return (error_func(file, NOT_CREATE));
	write(fd, file->header, all->header_size);
	write(fd, file->prog_content, file->prog_size);
	close(fd);
	ft_printf("<bgreen>File %s compiled to %s\n</>", file->s_name, file_name);
	return (0);
}
