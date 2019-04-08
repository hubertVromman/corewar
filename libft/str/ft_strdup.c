/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 11:55:44 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/02 15:11:48 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		count;
	char		*dest;
	size_t		count_to_copy;

	count = 0;
	while (s1 && s1[count])
		count++;
	dest = (char*)ft_memalloc(sizeof(char) * (count + 1));
	count_to_copy = 0;
	if (dest)
	{
		while (s1[count_to_copy])
		{
			dest[count_to_copy] = s1[count_to_copy];
			count_to_copy++;
		}
		if (count_to_copy == count)
		{
			dest[count_to_copy] = '\0';
			return (dest);
		}
	}
	ft_strdel(&dest);
	return (NULL);
}
