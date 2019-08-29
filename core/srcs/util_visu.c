/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 03:11:00 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/20 20:36:54 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		write_to_buf(t_printable *strct, char c, int f_color, int b_color)
{
	strct->to_print = c;
	strct->fore_color = f_color & 0x00ffffff;
	strct->back_color = b_color & 0x00ffffff;
	return (0);
}

int		add_str_to_buffer(t_printable *strct, char *str, int f_color, int b_color)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			write_to_buf(strct + i, str[i], f_color, b_color);
		}
	}
	return (0);
}

int		add_name_to_buffer(t_printable *strct, char *str, int f_color, int b_color)
{
	int		i;

	i = -1;
	while (str[++i] && i < MAX_NAME_LENGTH)
	{
		if (str[i] != ' ')
		{
			write_to_buf(strct + i, str[i], f_color, b_color);
		}
	}
	return (0);
}
