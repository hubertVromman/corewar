/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 15:22:25 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/03 15:22:27 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	len;
	int		count;
	char	*hay;

	if (!*needle)
		return ((char *)haystack);
	if (!*haystack)
		return (NULL);
	len = ft_strlen(needle);
	hay = (char *)haystack;
	count = -1;
	while (hay[++count])
		if (!strncmp(hay + count, needle, len))
			return (hay + count);
	return (NULL);
}
