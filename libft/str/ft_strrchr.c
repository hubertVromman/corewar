/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 15:19:27 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/03 15:19:29 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memrchr(const void *s, int c, size_t n)
{
	if (*(unsigned char*)s == (unsigned char)c)
		return ((void*)s);
	return ((n) ? ft_memrchr(s - 1, c, n - 1) : NULL);
}

char		*ft_strrchr(const char *s, int c)
{
	return ((char *)ft_memrchr(s + ft_strlen(s), c, ft_strlen(s)));
}
