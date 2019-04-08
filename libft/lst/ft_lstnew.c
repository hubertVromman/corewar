/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:45:43 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/04 15:45:46 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*to_return;

	if (content)
	{
		to_return = (t_list*)ft_memalloc(sizeof(t_list));
		if (to_return)
		{
			to_return->content = ft_memalloc(content_size);
			if (to_return->content)
			{
				ft_memmove(to_return->content, content, content_size);
				to_return->content_size = content_size;
			}
		}
	}
	else
	{
		to_return = (t_list*)ft_memalloc(sizeof(t_list));
		if (to_return)
		{
			to_return->content_size = 0;
			to_return->content = NULL;
		}
	}
	return (to_return);
}
