/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_indexof.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:28:03 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/27 14:28:05 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_last_indexof(char const *str, char to_find)
{
	int		count;

	if (!str)
		return (-1);
	count = ft_strlen(str);
	while (count > -1 && str[count] != to_find)
		count--;
	return (count);
}
