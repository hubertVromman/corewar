/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 15:36:35 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/03 15:36:37 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		count;

	count = 0;
	if (!*haystack || len < 1)
		return (NULL);
	while (haystack[count] && needle[count] && haystack[count] == needle[count])
		count++;
	return ((!needle[count] && count <= len) ? (char*)haystack :
		ft_strnstr(haystack + 1, needle, len - 1));
}
