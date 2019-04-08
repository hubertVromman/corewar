/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:33:21 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/02 15:33:23 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		length;
	int		offset;

	if (!s)
		return ((char*)s);
	offset = 0;
	while (s[offset] == ' ' || s[offset] == '\t' || s[offset] == '\n')
		offset++;
	if (!s[offset])
		return (ft_strnew(0));
	length = ft_strlen((char*)s) - offset - 1;
	while (s[length + offset] == ' ' || s[length + offset] == '\t'
		|| s[length + offset] == '\n')
		length--;
	return (ft_strsub(s, offset, length + 1));
}
