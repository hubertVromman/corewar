/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 02:28:56 by sofchami          #+#    #+#             */
/*   Updated: 2019/08/07 03:29:04 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_header()
{
	int		offset_x;

	offset_x = g_all.visu.nb_cols / 2 - 21;
	ft_printf("<b>");
	jump_to(offset_x, 1);
	ft_printf("   _____                                  ");
	jump_to(offset_x, 2);
	ft_printf("  / ____|                                 ");
	jump_to(offset_x, 3);
	ft_printf(" | |     ___  _ __ _____      ____ _ _ __ ");
	jump_to(offset_x, 4);
	ft_printf(" | |    / _ \\| '__/ _ \\ \\ /\\ / / _` | '__|");
	jump_to(offset_x, 5);
	ft_printf(" | |___| (_) | | |  __/\\ V  V / (_| | |   ");
	jump_to(offset_x, 6);
	ft_printf("  \\_____\\___/|_|  \\___| \\_/\\_/ \\__,_|_|   ");
	jump_to(offset_x, 7);
	ft_printf("                                          ");
	ft_printf("</>");
return (0000);
}

int		print_proces_info(int i)
{
	int k;
	int n;
	int l;
	int opcode;

	n = -1;
	l = 0;
	jump_to(X, i);
	ft_printf("%1$/40c All proces %1$/40c\n", '-');
	i++;
	while (++n < g_all.nb_champ)
	{
		k = -1;
		while (++k < g_all.champ[n].nb_proces)
		{
			jump_to(X, i + k + l);
			opcode = g_all.champ[n].proces[k].opcode;
			ft_printf("player_nb %2d  |  proces_id %3d  |  pc %4d  |  opcode " CHAR_HEX_PRINT "  |  Name OP %5s  |  cycle_left %4d\n", g_all.champ[n].player_nb, g_all.champ[n].proces[k].id_proces, g_all.champ[n].proces[k].pc, opcode, opcode > 0 && opcode < 16 ? g_op_tab[opcode - 1].name : "null", g_all.champ[n].proces[k].cycle_left);
		}
		l += k;
	}
	return (0);
}

int		print_player_info(int i)
{
	int k;

	k = -1;
	while (++k < g_all.nb_champ)
	{
		jump_to(X, i);
		ft_printf("PLAYER %d : ", g_all.champ[k].player_nb);
		jump_to(X + 12, i);
		ft_printf(RGB_PRINT "%s", (g_all.champ[k].color_rgb >> 16) & 0xff, (g_all.champ[k].color_rgb >> 8) & 0xff, (g_all.champ[k].color_rgb >> 0) & 0xff, g_all.champ[k].player_name);
		i++;
		jump_to(X + 5, i);
		ft_printf(RESET_COLOR "Last live : %1$/20c %d", ' ', g_all.champ[k].lives_period);
		i+=2;
	}
	i++;
	return (i);
}

int		print_init_info(int i)
{
	int lives;

	lives = 0;
	while (++i < g_all.nb_champ)
		lives += g_all.champ[i].lives_period;
	jump_to(X, HEADER_HEIGHT);
	ft_printf(RESET_COLOR "%1$/42c Info %1$/42c\n", '-');
	i = 0;
	while (++i < 6)
	{
		jump_to(X, i + HEADER_HEIGHT);
		i == 1 ? ft_printf("Cycles        : %4d", g_all.cycle) : 0;
		// i == 2 ? ft_printf("Cycles/second limit : %4d", g_all.visu.max_cps) : 0;
		i == 3 ? ft_printf("Nbr de proces : %4d", g_all.nb_proces_tot) : 0;
		i == 4 ? ft_printf("Lives period  : %4d", lives) : 0;
		i == 5 ? ft_printf("Cycle to die  : %4d", g_all.cycle_to_die) : 0;
	}
	i+=HEADER_HEIGHT;
	i++;
	i = print_player_info(i);
	i++;
	return (i);
}

int		print_vm_info()
{
	int i;

	i = print_init_info(-1);
	print_proces_info(i);
	if (g_all.max_proces <= g_all.nb_proces_tot)
		g_all.max_proces = g_all.nb_proces_tot;
	else
	{
		int tmp;
		tmp = g_all.nb_proces_tot + i;
		while (tmp < g_all.max_proces + i)
		{
			jump_to(X, tmp);
			ft_printf("%1$/80c", ' ');
			tmp++;
		}
		g_all.max_proces = g_all.nb_proces_tot;
	}
	return (0);
}
