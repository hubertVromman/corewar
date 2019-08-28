/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:50:02 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/14 23:01:35 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		operation_aff(t_champ *champ, t_proces *proces, t_arg *args)
{
	char	to_print;

	to_print = proces->reg[args[0].value];
	champ = NULL;
	if (g_all.flags[VISU])
	{
		if (to_print < 32 || to_print >= 127)
			to_print = ' ';
		if (g_all.visu.size_aff == INFO_WIDTH - 13)
		{
			ft_memcpy(g_all.visu.aff_string, g_all.visu.aff_string + 1, g_all.visu.size_aff - 1);
			g_all.visu.aff_string[g_all.visu.size_aff - 1] = to_print;
			add_string_to_buffer(g_all.visu.next_frame + (HEADER_HEIGHT + 6) * g_all.visu.nb_cols + X + 5, g_all.visu.aff_string, 0xffffff, 0);
		}
		else
		{
			if (!(g_all.visu.aff_string = realloc(g_all.visu.aff_string, g_all.visu.size_aff + 1)))
				exit_func(MERROR, 0);
			g_all.visu.aff_string[g_all.visu.size_aff] = to_print;
			if (g_all.visu.size_aff)
				write_to_buffer(g_all.visu.next_frame + (HEADER_HEIGHT + 6) * g_all.visu.nb_cols + X + 4 + g_all.visu.size_aff, g_all.visu.aff_string[g_all.visu.size_aff - 1], 0x00ffffff, 0);
			g_all.visu.size_aff++;
		}
		write_to_buffer(g_all.visu.next_frame + (HEADER_HEIGHT + 6) * g_all.visu.nb_cols + X + 4 + g_all.visu.size_aff, to_print, proces->color_rgb, 0);
	}
	else if (g_all.flags[INFORMATION])
		ft_printf("Aff: %c\n", to_print);
	proces->carry = proces->reg[args[0].value] == 0 ? 1 : 0;
	return (1);
}
