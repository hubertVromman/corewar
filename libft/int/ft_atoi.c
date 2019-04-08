/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 16:34:37 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/08 12:57:32 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long	int_to_return;
	int		sign;

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
	while (*str <= '9' && *str >= '0')
	{
		if (int_to_return > 922337203685477581 || (int_to_return
	== 922337203685477580 && (*str - '0') > 6 + ((sign > 0) ? 0 : 1)))
			return ((sign > 0) ? -1 : 0);
		int_to_return = int_to_return * 10 + *str - '0';
		str++;
	}
	return (sign * int_to_return);
}
