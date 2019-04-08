/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 12:46:18 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/24 12:46:19 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_tab(void ***tab)
{
	int count;

	if (!tab || !*tab)
		return ;
	count = 0;
	while ((*tab)[count])
	{
		ft_memdel(&(*tab)[count++]);
	}
	free(*tab);
	*tab = NULL;
}
