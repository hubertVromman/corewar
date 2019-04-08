/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:13:54 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/02 15:13:56 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*to_return;
	unsigned int	count;

	if (!s)
		return (NULL);
	to_return = ft_strnew(len);
	if (to_return)
	{
		count = -1;
		while (++count < len)
			to_return[count] = s[start + count];
	}
	return (to_return);
}
