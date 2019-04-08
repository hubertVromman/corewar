/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:51:57 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/05 14:51:58 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		gloat_func(long double nb, char *f, int w[2], int is_upper)
{
	int			exp;

	exp = exponent(&nb, 0);
	if (w[1] == -1)
		w[1] = 6;
	if (exp < -4 || exp >= (w[1] ? w[1] : 1))
	{
		w[1] -= 1;
		return (eloat_func(nb, f, w, is_upper));
	}
	else
	{
		w[1] -= exp + 1;
		return (float_func(nb, f, w));
	}
}
