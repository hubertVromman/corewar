/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:02:14 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/12 17:02:15 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		parse_lines(t_file *file, char *data)
{
	while (1)
	{
		file->inline_off = skip_whitespaces(data, file->glob_off);
		if (data[file->glob_off + file->inline_off] == '\n')
			end_of_line(file);
		else
		{
			// if (get_command_name(file, data) == -1)
			return (-1);
		}
	}
	return (0);
}

int		create_code(t_a *all, t_file *file)
{
	if (all->flags[0])
		;
	parse_lines(file, file->s_file_content);
	return (0);
}
