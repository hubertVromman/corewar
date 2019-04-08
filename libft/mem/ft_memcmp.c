/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 15:56:10 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/03 15:56:11 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n > 0)
		return ((*(unsigned char*)s1 - *(unsigned char*)s2) ?
				(*(unsigned char*)s1 - *(unsigned char*)s2) :
				ft_memcmp(s1 + 1, s2 + 1, n - 1));
		return (0);
}
