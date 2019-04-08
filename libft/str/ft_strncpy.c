/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 11:45:51 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/04 11:45:52 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	length_src;
	size_t	count;

	length_src = ft_strlen(src);
	if (length_src < len)
	{
		ft_strcpy(dst, src);
		count = -1;
		while (++count < len - length_src)
			dst[length_src + count] = 0;
	}
	else if (len > 0)
	{
		*dst = *src;
		return (ft_strncpy(dst + 1, src + 1, len - 1) - 1);
	}
	return (dst);
}
