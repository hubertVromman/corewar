/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:13:07 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/02 15:13:12 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		count;
	int		length;
	char	*to_return;

	if (!s)
		return (NULL);
	length = ft_strlen((char*)s);
	to_return = (char*)malloc(sizeof(char) * (length + 1));
	if (to_return)
	{
		count = -1;
		while (++count < length)
			to_return[count] = f(s[count]);
		to_return[count] = 0;
	}
	return (to_return);
}
