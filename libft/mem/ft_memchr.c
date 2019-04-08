/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:54:10 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/08 12:51:45 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (n > 0 && *(unsigned char*)s == (unsigned char)c)
		return ((void*)s);
	return (n > 1 ? ft_memchr(s + 1, c, n - 1) : NULL);
}
