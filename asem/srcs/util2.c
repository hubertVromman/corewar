/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:38:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/25 13:38:33 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		nb_digits_base(char *str, char *base, int c, int *which_base)
{
	while (ft_indexof(base, str[c]) != -1)
		c++;
	*which_base = ft_strlen(base);
	return (c);
}

int		nb_digits(char *str, int *which_base)
{
	int		c;

	c = *str == '-';
	if (which_base && (g_all.flags[OTHER_BASE] || g_all.file->extend)
		&& *str == '0')
	{
		c++;
		if (str[c] == 'x')
			c = nb_digits_base(str, "0123456789abcdef", c + 1, which_base);
		else if (str[c] == 'b')
			c = nb_digits_base(str, "01", c + 1, which_base);
		else
			c = nb_digits_base(str, "01234567", c, which_base);
		return (c);
	}
	while (ft_isdigit(str[c]))
		c++;
	if (which_base)
		*which_base = 10;
	return (c);
}

int		get_normal_base(char *data, int base)
{
	if (base == 2)
		return (ft_atoi_base(data + 2, "01"));
	else if (base == 8)
		return (ft_atoi_base(data + 1, "01234567"));
	else if (base == 10)
		return (ft_atoi(data));
	else if (base == 16)
		return (ft_atoi_base(data + 2, "0123456789abcdef"));
	else
		return (-1);
}
