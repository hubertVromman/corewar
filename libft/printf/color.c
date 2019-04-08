/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:28:22 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/05 16:28:23 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_bui(char *fm, int *count, char buicolor[19])
{
	if (fm[*count] == 'b' && (fm[*count + 1] == 'u' || fm[*count + 1] == 'i'
				|| fm[*count + 1] == ' ' || fm[*count + 1] == '>'))
		buicolor[0] = 1;
	else if (fm[*count] == 'u')
		buicolor[1] = 1;
	else if (fm[*count] == 'i')
		buicolor[2] = 1;
	else
		return (0);
	if (fm[*count + 1] == ' ')
		(*count)++;
	else if (fm[*count + 1] != 'u' && fm[*count + 1] != 'b' &&
		fm[*count + 1] != 'i' && fm[*count + 1] != '>')
		return (0);
	return (1);
}

int		end_fail(char **fm)
{
	char	*created;

	if (!(created = realloc_g_str(1)))
		return (-1);
	created[0] = '<';
	(*fm)++;
	return (0);
}

int		end_succes(char **fm, char buicolor[19], int end_bal, int pos_end)
{
	int		count;

	count = -1;
	while (++count < 19)
		if (buicolor[count])
			g_color[count] = !end_bal;
	if (change_status())
		return (-1);
	(*fm) += pos_end + 1;
	return (0);
}

int		instanciate_var(char **fm, int *pos, int *pos_end, int *count)
{
	if (!(g_str = ft_strljoin(g_str, *fm, -1, *pos)))
		return (-1);
	else
		(*fm) += *pos;
	*pos = -1;
	*pos_end = ft_indexof(*fm, '>');
	if (*pos_end == -1 || *pos_end == 1)
		return (end_fail(fm));
	*count = 1;
	return (1);
}

int		balise_func(char **fm, int *pos)
{
	int		pos_end;
	int		count;
	int		end_bal;
	char	buicolor[19];

	if ((end_bal = instanciate_var(fm, pos, &pos_end, &count)) != 1)
		return (end_bal);
	end_bal = 0;
	ft_memset(buicolor, 0, 19);
	if ((*fm)[count] == '/' && (end_bal = 1) && (count++))
		if ((*fm)[count] == '>' && ft_memset(buicolor, 1, 19))
			return (end_succes(fm, buicolor, end_bal, pos_end));
	while (count < pos_end && is_bui(*fm, &count, buicolor))
		count++;
	if ((*fm)[count] == '>')
		return (end_succes(fm, buicolor, end_bal, pos_end));
	if (count < pos_end)
		is_color(*fm, &count, buicolor);
	if (count != -1 && (*fm)[count] == '>')
		return (end_succes(fm, buicolor, end_bal, pos_end));
	return (end_fail(fm));
}
