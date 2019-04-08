/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 11:44:08 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/27 11:44:15 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		e(va_list ap, int to_return)
{
	if (!to_return && g_output != -1)
		write(g_output, g_str, g_len);
	if (g_output != -1)
		ft_strdel(&g_str);
	else
		*g_outstr = g_str;
	ft_strdel(&g_color);
	va_end(ap);
	return (to_return ? -1 : g_len);
}

int		dollar(char **s, va_list ap)
{
	int		pos;

	if (ft_isdigit(**s) && ft_indexof(*s, '$') != -1)
	{
		va_end(ap);
		pos = ft_atoi(*s);
		while (**s != '$')
			(*s)++;
		(*s)++;
		return (pos);
	}
	return (-1);
}

void	skip_useless(int pos, va_list ap)
{
	while (--pos > 0)
		va_arg(ap, int);
}

int		instanciate_variable(const char *restrict format, char **s)
{
	if (!format)
		return (-1);
	*s = (char*)format;
	g_len = 0;
	g_output = 1;
	g_outstr = NULL;
	if (!(g_str = format ? ft_strnew(0) : ft_strdup("(null)")))
		return (-1);
	if (!(g_color = ft_strnew(19)))
		return (-1);
	return (0);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	char		*s;
	int			p[2];

	va_start(ap, format);
	if (instanciate_variable(format, &s))
		return (e(ap, -1));
	while ((p[0] = ft_indexof(s, '%')) || 1)
		if ((p[1] = ft_indexof(s, '<')) != -1 && (p[0] == -1 || p[1] < p[0]))
			balise_func(&s, &p[1]);
		else if (p[0] != -1)
		{
			if (!(g_str = ft_strljoin(g_str, s, -1, p[0])))
				return (e(ap, -1));
			if ((s += p[0] + 1) && (p[0] = dollar(&s, ap)) != -1)
			{
				va_start(ap, format);
				skip_useless(p[0], ap);
			}
			if (parser(ap, &s))
				return (e(ap, -1));
		}
		else
			break ;
	return (e(ap, (g_str = ft_strljoin(g_str, s, -1, -1)) ? 0 : -1));
}
