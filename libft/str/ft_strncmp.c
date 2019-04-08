/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 15:43:24 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/03 15:43:30 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if ((*s1 || *s2) && n > 0)
		return ((*(unsigned char*)s1 - *(unsigned char*)s2) ?
			(*(unsigned char*)s1 - *(unsigned char*)s2) :
			ft_strncmp(s1 + 1, s2 + 1, n - 1));
		return (0);
}
