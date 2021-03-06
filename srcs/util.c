/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 10:12:44 by hvromman          #+#    #+#             */
/*   Updated: 2019/07/08 10:12:46 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		change_endianness(int little)
{
	int		big;

	big = ((little >> 24) & 0xff) |
		((little >> 8) & 0xff00) |
		((little << 8) & 0xff0000) |
		((little << 24) & 0xff000000);
	return (big);
}

char	*get_ext(char *str)
{
	int		offset;

	offset = ft_last_indexof(str, '.');
	if (offset == -1 && ft_strlen(str) == 1)
		return (str + 1);
	return (str + offset + 1);
}
