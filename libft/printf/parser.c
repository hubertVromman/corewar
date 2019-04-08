/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 12:51:38 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/28 12:51:40 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_width2(char **fm)
{
	int		to_return;

	to_return = ft_atoi(*fm);
	while (ft_isdigit(**fm))
		(*fm)++;
	(*fm)--;
	return (to_return);
}

int		check_width(char *flag, va_list ap)
{
	int		to_return;

	to_return = va_arg(ap, int);
	if (to_return < 0)
	{
		flag[3] = 1;
		to_return *= -1;
	}
	return (to_return);
}

int		check_prec(char **fm, va_list ap)
{
	int		to_return;

	(*fm)++;
	if (**fm == '*')
	{
		to_return = va_arg(ap, int);
		if (to_return < -1)
			to_return = -1;
		return (to_return);
	}
	to_return = ft_atoi(*fm);
	while (ft_isdigit(**fm))
		(*fm)++;
	(*fm)--;
	return (to_return);
}

void	check_convert(char fm, char *f)
{
	int		to_write;

	to_write = 7;
	if (f[to_write] &&
	ft_indexof(MODIFIER, fm) <= ft_indexof(MODIFIER, f[to_write]))
		to_write--;
	f[to_write] = fm;
}

int		parser(va_list ap, char **fm)
{
	char	*f;
	int		w[2];
	int		ret;

	if (start(&f, w, fm, ap))
		return (-1);
	while (**fm)
	{
		if ((ret = ft_indexof(FLAG, **fm)) != -1)
			f[ret] = 1;
		else if (**fm == '.' || **fm == '/')
			**fm == '.' ? (w[1] = check_prec(fm, ap)) :
			(f[9] = check_prec(fm, ap));
		else if (ft_isdigit(**fm))
			w[0] = check_width2(fm);
		else if (**fm == '*')
			w[0] = check_width(f, ap);
		else if (ft_indexof(MODIFIER, **fm) != -1)
			check_convert(**fm, f);
		else
			break ;
		(*fm)++;
	}
	return (end(f, fm) ? 0 : go_to_right_func(ap, f, w));
}
