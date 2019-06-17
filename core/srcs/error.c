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
	ft_printf("<b bwhite>%s: <bred>error:<b bwhite> %>", champ->file_name, 2);
	if (error_code == NOT_COR_FILE)
		ft_printf("not a .cor file\n%>", 2);
	else if (error_code == OPEN_FAIL)
		ft_printf("open failed\n%>", 2);
	// else if (error_code == NOT_CREATE)
	// 	ft_printf("could not open or create %s\n%>", file->cor_name, 2);
	// else if (error_code == NAME_TOO_LONG)
	// 	ft_printf("program name too long (max size : %d)\n%>",
	// 		PROG_NAME_LENGTH, 2);
	// else if (error_code == NAME_NOT_FOUND)
	// 	ft_printf("program name not found\n%>", 2);
	// else if (error_code == COMMENT_TOO_LONG)
	// 	ft_printf("program comment too long (max size : %d)\n%>",
	// 		COMMENT_LENGTH, 2);
	// else if (error_code == COMMENT_NOT_FOUND)
	// 	ft_printf("program comment not found\n%>", 2);
	else
		ft_printf("undifined error\n%>", 2);
	ft_printf("</>%>", 2);
	g_all.nb_errors++;
	champ->nb_errors++;
	return (-1);
}
