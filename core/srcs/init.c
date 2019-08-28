/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:12:55 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/28 01:12:57 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		init_func_pointer()
{
	g_all.func[0] = &operation_live;
	g_all.func[1] = &operation_ld;
	g_all.func[2] = &operation_st;
	g_all.func[3] = &operation_add;
	g_all.func[4] = &operation_sub;
	g_all.func[5] = &operation_and;
	g_all.func[6] = &operation_or;
	g_all.func[7] = &operation_xor;
	g_all.func[8] = &operation_zjmp;
	g_all.func[9] = &operation_ldi;
	g_all.func[10] = &operation_sti;
	g_all.func[11] = &operation_fork;
	g_all.func[12] = &operation_lld;
	g_all.func[13] = &operation_lldi;
	g_all.func[14] = &operation_lfork;
	g_all.func[15] = &operation_aff;
	return (0);
}

static int		sort_champs()
{
	int		i;
	t_champ	tmp;

	i = -1;
	while (++i < g_all.nb_champ - 1)
	{
		if (g_all.champ[i].player_nb > g_all.champ[i + 1].player_nb)
		{
			ft_memcpy(&tmp, &g_all.champ[i], sizeof(t_champ));
			ft_memcpy(&g_all.champ[i], &g_all.champ[i + 1], sizeof(t_champ));
			ft_memcpy(&g_all.champ[i + 1], &tmp, sizeof(t_champ));
			i = -1;
		}
	}
	return (0);
}

int		init_all(int ac, char **av)
{
	int i;

	i = -1;
	ft_bzero(&g_all, sizeof(g_all));
	g_all.header_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	g_all.cycle_to_die = CYCLE_TO_DIE;
	parse_arg(ac, av);
	if (g_all.nb_champ < 1 || g_all.nb_champ > 4)
		exit_func(-1, 1);
	g_all.pos_depart = MEM_SIZE / g_all.nb_champ;
	sort_champs();
	if (g_all.flags[VISU])
		init_visu();
	while (++i < g_all.nb_champ)
	{
		g_all.champ[i].player_nb_arena = -g_all.champ[i].player_nb;
		ft_memcpy(g_all.arena + (g_all.pos_depart * i),
			g_all.champ[i].exec_file, g_all.champ[i].exec_size);
		create_proces(g_all.pos_depart * i, NULL, &(g_all.champ[i])); //gestion d'erreur
		g_all.champ[i].proces[0].opcode = g_all.arena[g_all.champ[i].proces->pc];
		g_all.champ[i].proces[0].cycle_left = get_cycle_left(g_all.champ[i].proces->opcode);
	}
	init_func_pointer();
	return (0);
}
