/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 12:05:25 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/08 12:52:26 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	total_length;
	size_t	count_dst;
	size_t	count_src;

	count_dst = ft_strlen(dst);
	total_length = ((ft_strlen(dst) < size) ? ft_strlen(dst) :
					size) + ft_strlen(src);
	count_src = 0;
	if (size > 0)
	{
		while (count_dst < size - 1)
			dst[count_dst++] = src[count_src++];
		dst[count_dst] = 0;
	}
	return (total_length);
}
