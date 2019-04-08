/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:59:24 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/21 13:59:25 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		bin_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	if (pos == 1)
		return (binary_func(va_arg(ap, unsigned int), f, w));
	else if (pos == 2)
	{
		if (f[6] == 'l')
			return (binary_func(va_arg(ap, unsigned long), f, w));
		else if (f[6] == 'h')
			return (binary_func((unsigned short)
				va_arg(ap, unsigned int), f, w));
		else if (f[6] == 'j')
			return (binary_func(va_arg(ap, uintmax_t), f, w));
		else if (f[6] == 'z')
			return (binary_func(va_arg(ap, size_t), f, w));
	}
	else
	{
		if (f[6] == 'l')
			return (binary_func(va_arg(ap, unsigned long long), f, w));
		else if (f[6] == 'h')
			return (binary_func((unsigned char)va_arg(ap, unsigned int), f, w));
	}
	return (binary_func(va_arg(ap, unsigned int), f, w));
}

int		num_dispatcher(va_list ap, char *f, int pos)
{
	if (pos == 1)
		return (n_intfunc(va_arg(ap, int*), f));
	else if (pos == 2)
	{
		if (f[6] == 'l')
			return (n_longfunc(va_arg(ap, long*), f));
		else if (f[6] == 'h')
			return (n_shortfunc((short*)va_arg(ap, int*), f));
		else if (f[6] == 'j')
			return (n_intmaxtfunc(va_arg(ap, intmax_t*), f));
		else if (f[6] == 'z')
			return (n_ssizetfunc(va_arg(ap, ssize_t*), f));
	}
	else
	{
		if (f[6] == 'l')
			return (n_longlongfunc(va_arg(ap, long long*), f));
		else if (f[6] == 'h')
			return (n_charfunc((char*)va_arg(ap, int*), f));
	}
	return (n_intfunc(va_arg(ap, int*), f));
}

int		efl_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	int		length;

	length = ft_strlen(f + 6);
	if (f[5 + length] == 'e')
	{
		if (pos == 2 && f[6] == 'L')
			return (eloat_func(va_arg(ap, long double), f, w, 0));
		return (eloat_func(va_arg(ap, double), f, w, 0));
	}
	if (pos == 2 && f[6] == 'L')
		return (eloat_func(va_arg(ap, long double), f, w, 1));
	return (eloat_func(va_arg(ap, double), f, w, 1));
}

int		flo_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	int		length;

	length = ft_strlen(f + 6);
	if (f[5 + length] == 'f')
	{
		if (pos == 2 && f[6] == 'L')
			return (float_func(va_arg(ap, long double), f, w));
		return (float_func(va_arg(ap, double), f, w));
	}
	if (pos == 2 && f[6] == 'L')
		return (float_func(va_arg(ap, long double), f, w));
	return (float_func(va_arg(ap, double), f, w));
}

int		gfl_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	int		length;

	length = ft_strlen(f + 6);
	if (f[5 + length] == 'g')
	{
		if (pos == 2 && f[6] == 'L')
			return (gloat_func(va_arg(ap, long double), f, w, 0));
		return (gloat_func(va_arg(ap, double), f, w, 0));
	}
	if (pos == 2 && f[6] == 'L')
		return (gloat_func(va_arg(ap, long double), f, w, 1));
	return (gloat_func(va_arg(ap, double), f, w, 1));
}
