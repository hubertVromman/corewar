/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_func1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:37:20 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 14:37:24 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		n_intfunc(int *n, char *flag)
{
	*n = g_len;
	free(flag);
	return (0);
}

int		n_longfunc(long *n, char *flag)
{
	*n = g_len;
	free(flag);
	return (0);
}

int		n_longlongfunc(long long *n, char *flag)
{
	*n = g_len;
	free(flag);
	return (0);
}

int		n_shortfunc(short *n, char *flag)
{
	*n = g_len;
	free(flag);
	return (0);
}

int		n_charfunc(char *n, char *flag)
{
	*n = g_len;
	free(flag);
	return (0);
}
