/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispacher.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 15:04:53 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 15:04:55 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		cha_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	if (pos == 2 && f[6] == 'l')
		return (lchar_func(va_arg(ap, wint_t), f, w));
	return (char_func(va_arg(ap, int), f, w));
}

int		str_dispatcher(va_list ap, char *f, int w[2], int pos)
{
	if (pos == 2 && f[6] == 'l')
		return (lstring_func(va_arg(ap, wchar_t*), f, w));
	return (string_func(va_arg(ap, char*), f, w, 0));
}

int		go_to_right_func3(va_list ap, char *f, int w[2], int ret)
{
	int		length;

	length = ft_strlen(f + 6);
	if (ret == 22)
		return (bin_dispatcher(ap, f, w, length));
	else if (ret == 23)
		return (rtring_func(va_arg(ap, char*), f, w));
	else if (ret == 24)
		return (output_file_func(ap, f));
	return (-1);
}

int		go_to_right_func2(va_list ap, char *f, int w[2], int ret)
{
	int		length;

	length = ft_strlen(f + 6);
	if (ret == 9)
		return (p_func(va_arg(ap, uintmax_t), f, w));
	else if (ret == 10)
		return (signed_func(va_arg(ap, long), f, w));
	else if (ret == 11)
		return (unsigned_func(va_arg(ap, unsigned long), f, w));
	else if (ret == 12)
		return (octal_func(va_arg(ap, unsigned long), f, w));
	else if (ret == 13)
		return (lchar_func(va_arg(ap, wint_t), f, w));
	else if (ret == 14)
		return (lstring_func(va_arg(ap, wchar_t*), f, w));
	else if (ret == 15 || ret == 16)
		return (flo_dispatcher(ap, f, w, length));
	else if (ret == 17 || ret == 18)
		return (gfl_dispatcher(ap, f, w, length));
	else if (ret == 19 || ret == 20)
		return (efl_dispatcher(ap, f, w, length));
	else if (ret == 21)
		return (num_dispatcher(ap, f, length));
	else
		return (go_to_right_func3(ap, f, w, ret));
}

int		go_to_right_func(va_list ap, char *f, int w[2])
{
	int		length;
	char	ret;

	length = ft_strlen(f + 6) > 2 ? 3 : ft_strlen(f + 6);
	if ((ret = ft_indexof(CONVERTER, f[5 + length])) == -1)
		return (not_correct_flag(f, w));
	else if (ret == 0 || ret == 1)
		return (int_dispatcher(ap, f, w, length));
	else if (ret == 2)
		return (uns_dispatcher(ap, f, w, length));
	else if (ret == 3)
		return (oct_dispatcher(ap, f, w, length));
	else if (ret == 4)
		return (hex_dispatcher(ap, f, w, length));
	else if (ret == 5)
		return (mhe_dispatcher(ap, f, w, length));
	else if (ret == 6)
		return (cha_dispatcher(ap, f, w, length));
	else if (ret == 7)
		return (str_dispatcher(ap, f, w, length));
	else if (ret == 8)
		return (percent_func(f, w));
	else
		return (go_to_right_func2(ap, f, w, ret));
}
