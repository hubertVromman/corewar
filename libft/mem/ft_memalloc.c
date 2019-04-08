/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:07:54 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/02 15:07:57 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	count;

	mem = malloc(size);
	if (mem)
	{
		count = -1;
		while (++count < size)
			*(unsigned char*)&mem[count] = 0;
	}
	return (mem);
}
