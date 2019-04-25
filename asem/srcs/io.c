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

	if ((file->s_fd = open(file->s_name, O_RDONLY)) == -1)
		return (error_func(file, OPEN_FAIL));
	file->file_size = lseek(file->s_fd, 0, SEEK_END);
	lseek(file->s_fd, 0, SEEK_SET);
	file->s_file_content = malloc(file->file_size + 1);
	ret = read(file->s_fd, file->s_file_content, file->file_size);
	file->s_file_content[file->file_size] = 0;
	close(file->s_fd);
	return (ret < 0 ? -1 : 0);
}

int		write_file(t_a *all, t_file *file, char *file_name)
{
	file->cor_name = file_name;
	if (!file_name || file->nb_error)
		return (-1);
	if ((file->cor_fd = open(file_name,
		O_WRONLY | O_CREAT | O_TRUNC, 0755)) == -1)
		return (error_func(file, NOT_CREATE));
	write(file->cor_fd, file->header, all->header_size);
	write(file->cor_fd, file->prog_content, file->prog_size);
	close(file->cor_fd);
	return (0);
}
