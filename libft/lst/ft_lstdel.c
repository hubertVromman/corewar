/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:54:15 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/04 17:55:07 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*current;
	t_list	*next;

	next = *alst;
	current = next;
	while (current)
	{
		next = current->next;
		ft_lstdelone(&current, del);
		free(current);
		current = next;
	}
	*alst = NULL;
}
