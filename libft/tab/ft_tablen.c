/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 12:43:32 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/24 12:44:11 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tablen(void **tab)
{
	int		count;

	if (!tab)
		return (0);
	count = 0;
	while (tab[count])
		count++;
	return (count);
}
