/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:37:40 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/03 14:37:42 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	if (n > 0)
		*(unsigned char*)dst = *(unsigned char*)src;
	else
		return (NULL);
	if (*(unsigned char*)src == (unsigned char)c)
		return (dst + 1);
	return (ft_memccpy(dst + 1, src + 1, c, n - 1));
}
