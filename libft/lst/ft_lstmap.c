/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:55:49 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/04 17:55:51 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first_of_new;
	t_list	*current;

	first_of_new = NULL;
	while (lst)
	{
		if (!first_of_new)
		{
			current = (*f)(lst);
			first_of_new = current;
		}
		else
		{
			current->next = (*f)(lst);
			current = current->next;
		}
		lst = lst->next;
	}
	return (first_of_new);
}
