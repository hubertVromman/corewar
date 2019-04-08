/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 10:37:57 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/09 10:37:58 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_indexof(char const *str, char to_find)
{
	int		count;

	count = 0;
	if (!str)
		return (-1);
	while (str[count] && str[count] != to_find)
		count++;
	return (str[count] || !to_find ? count : -1);
}
