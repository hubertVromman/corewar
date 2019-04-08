/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:03:03 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/12 14:03:05 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	size_t	count_s1;
	size_t	count_s2;
	char	*to_return;
	size_t	length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen((char*)s1) + ((len > ft_strlen((char*)s2))
		? ft_strlen((char*)s2) : len);
	to_return = ft_strnew(length);
	if (to_return)
	{
		count_s1 = -1;
		while (s1[++count_s1])
			to_return[count_s1] = s1[count_s1];
		count_s2 = -1;
		while (++count_s2 < len && s2[count_s2])
			to_return[count_s1 + count_s2] = s2[count_s2];
	}
	return (to_return);
}
