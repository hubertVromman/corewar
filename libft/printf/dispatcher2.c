/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:59:17 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/21 13:59:20 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		int_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	if (pos == 1)
		return (signed_func(va_arg(ap, int), f, w));
	else if (pos == 2)
	{
		if (f[6] == 'l')
			return (signed_func(va_arg(ap, long), f, w));
		else if (f[6] == 'h')
			return (signed_func((short)va_arg(ap, int), f, w));
		else if (f[6] == 'j')
			return (signed_func(va_arg(ap, intmax_t), f, w));
		else if (f[6] == 'z')
			return (signed_func(va_arg(ap, ssize_t), f, w));
	}
	else
	{
		if (f[6] == 'l')
			return (signed_func(va_arg(ap, long long), f, w));
		else if (f[6] == 'h')
			return (signed_func((char)va_arg(ap, int), f, w));
	}
	return (signed_func(va_arg(ap, int), f, w));
}

int		oct_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	if (pos == 1)
		return (octal_func(va_arg(ap, unsigned int), f, w));
	else if (pos == 2)
	{
		if (f[6] == 'l')
			return (octal_func(va_arg(ap, unsigned long), f, w));
		else if (f[6] == 'h')
			return (octal_func((unsigned short)va_arg(ap, unsigned int), f, w));
		else if (f[6] == 'j')
			return (octal_func(va_arg(ap, uintmax_t), f, w));
		else if (f[6] == 'z')
			return (octal_func(va_arg(ap, size_t), f, w));
	}
	else
	{
		if (f[6] == 'l')
			return (octal_func(va_arg(ap, unsigned long long), f, w));
		else if (f[6] == 'h')
			return (octal_func((unsigned char)va_arg(ap, unsigned int), f, w));
	}
	return (octal_func(va_arg(ap, unsigned int), f, w));
}

int		uns_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	if (pos == 1)
		return (unsigned_func(va_arg(ap, unsigned int), f, w));
	else if (pos == 2)
	{
		if (f[6] == 'l')
			return (unsigned_func(va_arg(ap, unsigned long), f, w));
		else if (f[6] == 'h')
			return (unsigned_func((unsigned short)
				va_arg(ap, unsigned int), f, w));
		else if (f[6] == 'j')
			return (unsigned_func(va_arg(ap, uintmax_t), f, w));
		else if (f[6] == 'z')
			return (unsigned_func(va_arg(ap, size_t), f, w));
	}
	else
	{
		if (f[6] == 'l')
			return (unsigned_func(va_arg(ap, unsigned long long), f, w));
		else if (f[6] == 'h')
			return (unsigned_func((unsigned char)
				va_arg(ap, unsigned int), f, w));
	}
	return (unsigned_func(va_arg(ap, unsigned int), f, w));
}

int		hex_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	if (pos == 1)
		return (hex_func(va_arg(ap, unsigned int), f, w));
	else if (pos == 2)
	{
		if (f[6] == 'l')
			return (hex_func(va_arg(ap, unsigned long), f, w));
		else if (f[6] == 'h')
			return (hex_func((unsigned short)va_arg(ap, unsigned int), f, w));
		else if (f[6] == 'j')
			return (hex_func(va_arg(ap, uintmax_t), f, w));
		else if (f[6] == 'z')
			return (hex_func(va_arg(ap, size_t), f, w));
	}
	else
	{
		if (f[6] == 'l')
			return (hex_func(va_arg(ap, unsigned long long), f, w));
		else if (f[6] == 'h')
			return (hex_func((unsigned char)va_arg(ap, unsigned int), f, w));
	}
	return (hex_func(va_arg(ap, unsigned int), f, w));
}

int		mhe_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	if (pos == 1)
		return (mhex_func(va_arg(ap, unsigned int), f, w));
	else if (pos == 2)
	{
		if (f[6] == 'l')
			return (mhex_func(va_arg(ap, unsigned long), f, w));
		else if (f[6] == 'h')
			return (mhex_func((unsigned short)va_arg(ap, unsigned int), f, w));
		else if (f[6] == 'j')
			return (mhex_func(va_arg(ap, uintmax_t), f, w));
		else if (f[6] == 'z')
			return (mhex_func(va_arg(ap, size_t), f, w));
	}
	else
	{
		if (f[6] == 'l')
			return (mhex_func(va_arg(ap, unsigned long long), f, w));
		else if (f[6] == 'h')
			return (mhex_func((unsigned char)va_arg(ap, unsigned int), f, w));
	}
	return (mhex_func(va_arg(ap, unsigned int), f, w));
}
