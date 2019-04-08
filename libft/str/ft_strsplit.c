/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:12:53 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/03 13:12:57 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	nb_of_str(char const *s, char c, int first)
{
	if (!*s)
		return (0);
	else if (*s == c)
		return (nb_of_str(s + 1, c, 0));
	else if (first)
		return (1 + nb_of_str(s + 1, c, 0));
	else
		return (nb_of_str(s + 1, c, 0) + ((*(s - 1) == c) ? 1 : 0));
}

static int	count_length(char const *str, char c)
{
	return ((*str != c && *str) ? 1 + count_length(str + 1, c) : 0);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**to_return;
	int		str_count;
	int		in_str_count;
	int		count;

	to_return = s ? (char**)malloc((sizeof(char*)) *
		(nb_of_str(s, c, 1) + 1)) : NULL;
	if (to_return)
	{
		count = 0;
		str_count = -1;
		while (s[count])
		{
			in_str_count = 0;
			if (s[count] != c && ((to_return[++str_count] =
		ft_strnew(count_length(&s[count], c))) || 1) && to_return[str_count])
				while (s[count] != c && s[count])
					to_return[str_count][in_str_count++] = s[count++];
			else
				count++;
		}
		to_return[++str_count] = NULL;
	}
	return (to_return);
}
