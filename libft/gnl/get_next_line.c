/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:15:23 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/06 16:15:24 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update(char **s)
{
	int		length;
	char	*tmp;

	length = ft_strlen(*s) + BUFF_SIZE;
	tmp = *s;
	if (!(*s = ft_strnew(length)))
	{
		free(tmp);
		return (NULL);
	}
	if (tmp)
		ft_strcpy(*s, tmp);
	free(tmp);
	return (*s + length - BUFF_SIZE);
}

int		swap(char **s, int r, char **line)
{
	char *tmp;

	*line = ft_strsub(*s, 0, r);
	tmp = *s;
	*s = ft_strdup(*s + r + 1);
	free(tmp);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*s[FOPEN_MAX];
	int			r;

	if (read(fd, NULL, 0))
		return (-1);
	if (s[fd] && (r = ft_indexof(s[fd], '\n')) != -1)
		return (swap(s + fd, r, line));
	while (read(fd, update(s + fd), BUFF_SIZE) > 0)
		if ((r = ft_indexof(s[fd], '\n')) != -1)
		{
			return (swap(s + fd, r, line));
		}
	if (!s[fd] || (!(*line = s[fd][0] ? ft_strdup(s[fd]) : NULL) && s[fd][0]))
		return (-1);
	ft_strdel(&s[fd]);
	return (*line ? 1 : 0);
}
