/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 17:12:45 by hvromman          #+#    #+#             */
/*   Updated: 2019/06/14 17:12:47 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		error_func(t_champ *champ, int error_code)
{
	if (champ)
		ft_printf("<b bwhite>%s: <bred>error:<b bwhite> %>", champ->file_name, 2);
	if (error_code == NOT_COR_FILE)
		ft_printf("not a .cor file\n%>", 2);
	else if (error_code == OPEN_FAIL)
		ft_printf("open failed\n%>", 2);
	else if (error_code == TOO_LARGE)
		ft_printf("too large executable (%d vs %d bytes)\n%>", champ->exec_size, CHAMP_MAX_SIZE, 2);
	else if (error_code == READ_ERROR)
		ft_printf("read error\n%>", 2);
	else if (error_code == INVALID_NB)
		ft_printf("invalid number : can't have negative player number\n%>", 2);
	else
		ft_printf("undifined error\n%>", 2);
	ft_printf("</>%>", 2);
	g_all.nb_errors++;
	if (champ)
		champ->nb_errors++;
	return (-1);
}
