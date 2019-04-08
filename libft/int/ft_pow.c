/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:40:31 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/29 13:40:33 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_pow(intmax_t number, size_t pow)
{
	intmax_t	to_return;

	to_return = 1;
	while (pow-- > 0)
		to_return *= number;
	return (to_return);
}
