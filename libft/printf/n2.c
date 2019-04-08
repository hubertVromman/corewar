/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_func2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:38:56 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 14:38:57 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		n_ssizetfunc(ssize_t *n, char *flag)
{
	*n = g_len;
	free(flag);
	return (0);
}

int		n_intmaxtfunc(intmax_t *n, char *flag)
{
	*n = g_len;
	free(flag);
	return (0);
}
