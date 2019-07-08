/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 09:55:50 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/26 09:55:52 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_base(const char *str, char *base)
{
	long	int_to_return;
	int		sign;
	int		nb;

	if (!base || ft_strlen(base) < 2)
		return (0);
	int_to_return = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
		*str == '\r' || *str == '\v' || *str == '\f')
		str++;
	sign = 1;
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	else if (*str == '+')
		str++;
	while (*str && (nb = ft_indexof(base, *str)) != -1)
	{
		int_to_return = int_to_return * ft_strlen(base) + nb;
		str++;
	}
	return (sign * int_to_return);
}
