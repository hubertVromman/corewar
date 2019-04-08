/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:13:43 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/02 15:13:45 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	size_t	count;
	char	*to_return;

	to_return = (char*)malloc(sizeof(char) * (size + 1));
	if (to_return)
	{
		count = -1;
		while (++count < size)
			to_return[count] = 0;
		to_return[count] = 0;
	}
	return (to_return);
}
