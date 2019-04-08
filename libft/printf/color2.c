/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:45:20 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/06 14:45:21 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_color2(char *fm, int *count, char buicolor[19])
{
	if (!ft_strncmp(fm + *count, "bblack", 6) && (*count += 6))
		buicolor[11] = 1;
	else if (!ft_strncmp(fm + *count, "bred", 4) && (*count += 4))
		buicolor[12] = 1;
	else if (!ft_strncmp(fm + *count, "bgreen", 6) && (*count += 6))
		buicolor[13] = 1;
	else if (!ft_strncmp(fm + *count, "byellow", 7) && (*count += 7))
		buicolor[14] = 1;
	else if (!ft_strncmp(fm + *count, "bblue", 5) && (*count += 5))
		buicolor[15] = 1;
	else if (!ft_strncmp(fm + *count, "bmagenta", 8) && (*count += 8))
		buicolor[16] = 1;
	else if (!ft_strncmp(fm + *count, "bcyan", 5) && (*count += 5))
		buicolor[17] = 1;
	else if (!ft_strncmp(fm + *count, "bwhite", 6) && (*count += 6))
		buicolor[18] = 1;
	else
	{
		*count = -1;
		return (0);
	}
	return (1);
}

int		is_color(char *fm, int *count, char buicolor[19])
{
	if (!ft_strncmp(fm + *count, "black", 5) && (*count += 5))
		buicolor[3] = 1;
	else if (!ft_strncmp(fm + *count, "red", 3) && (*count += 3))
		buicolor[4] = 1;
	else if (!ft_strncmp(fm + *count, "green", 5) && (*count += 5))
		buicolor[5] = 1;
	else if (!ft_strncmp(fm + *count, "yellow", 6) && (*count += 6))
		buicolor[6] = 1;
	else if (!ft_strncmp(fm + *count, "blue", 4) && (*count += 4))
		buicolor[7] = 1;
	else if (!ft_strncmp(fm + *count, "magenta", 7) && (*count += 7))
		buicolor[8] = 1;
	else if (!ft_strncmp(fm + *count, "cyan", 4) && (*count += 4))
		buicolor[9] = 1;
	else if (!ft_strncmp(fm + *count, "white", 5) && (*count += 5))
		buicolor[10] = 1;
	else
		return (is_color2(fm, count, buicolor));
	return (1);
}

char	*get_str2(int count)
{
	if (count == 11)
		return (BBLACK);
	else if (count == 12)
		return (BRED);
	else if (count == 13)
		return (BGREEN);
	else if (count == 14)
		return (BYELLOW);
	else if (count == 15)
		return (BBLUE);
	else if (count == 16)
		return (BMAGENTA);
	else if (count == 17)
		return (BCYAN);
	else if (count == 18)
		return (BWHITE);
	else
		return (get_str2(count));
}

char	*get_str(int count)
{
	if (count == 0)
		return (B);
	else if (count == 1)
		return (U);
	else if (count == 2)
		return (I);
	else if (count == 3)
		return (BLACK);
	else if (count == 4)
		return (RED);
	else if (count == 5)
		return (GREEN);
	else if (count == 6)
		return (YELLOW);
	else if (count == 7)
		return (BLUE);
	else if (count == 8)
		return (MAGENTA);
	else if (count == 9)
		return (CYAN);
	else if (count == 10)
		return (WHITE);
	else
		return (get_str2(count));
}

int		change_status(void)
{
	char	*created;
	int		size;
	int		i;
	int		count;

	size = 4;
	i = -1;
	while (++i < 19)
		if (g_color[i])
			size += i < 3 ? 4 : 5;
	if (!(created = realloc_g_str(size)))
		return (-1);
	i = -4;
	ft_memcpy(&created[i += 4], NC, 4);
	count = -1;
	while (++count < 19)
		if (g_color[count])
			ft_memcpy(&created[i += 4], get_str(count), count < 3 ? 4 : 5);
	return (0);
}
