/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:21:55 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/02 15:21:57 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		count_s1;
	int		count_s2;
	char	*to_return;
	int		length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	to_return = ft_strnew(length);
	if (to_return)
	{
		count_s1 = -1;
		while (s1[++count_s1])
			to_return[count_s1] = s1[count_s1];
		count_s2 = -1;
		while (s2[++count_s2])
			to_return[count_s1 + count_s2] = s2[count_s2];
	}
	return (to_return);
}
