/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 19:50:13 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 19:50:15 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		start(char **f, int w[2], char **fm, va_list ap)
{
	if (!fm || !*fm || !ap)
		return (-1);
	if (!(*f = ft_strnew(14)))
		return (-1);
	w[0] = -1;
	w[1] = -1;
	w[2] = 0;
	return (0);
}

int		end(char *f, char **fm, int w[3])
{
	ft_memcpy(f + 9, &(w[2]), 4);
	if (!**fm)
		return (-1);
	if (!f[7])
	{
		f[6] = **fm;
		f[7] = 0;
	}
	else if (f[6] != f[7])
	{
		f[6] = f[7];
		f[7] = **fm;
		f[8] = 0;
	}
	else
		f[8] = **fm;
	(*fm)++;
	if (f[1])
		f[0] = 0;
	if (f[3])
		f[2] = 0;
	if (*(int *)(f + 9) < 1)
		*(int *)(f + 9) = 1;
	return (0);
}
