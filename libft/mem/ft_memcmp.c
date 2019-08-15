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
	unsigned char *s1bis;
	unsigned char *s2bis;

	s1bis = (unsigned char *)s1;
	s2bis = (unsigned char *)s2;
	if (!n)
		return (0);
	while (*s1bis == *s2bis && --n)
	{
		s1bis++;
		s2bis++;
	}
	return (*s1bis - *s2bis);
}
