/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:16:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/31 10:12:54 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_cycle_left(int opcode)
{
	if (opcode < 1 || opcode > NB_OPERATIONS)
	{
		return (1);
	}
	else
		return (g_op_tab[opcode - 1].cycle_op);
}

int		calc_pc(int pc)
{
	return ((pc + MEM_SIZE) % MEM_SIZE);
}

int		read_arena_op(int pc)
{
	int		opcode;

	opcode = g_all.arena[pc];
	if (opcode < 1 || opcode > NB_OPERATIONS)
		return (0);
	return (opcode);
}

int		play_sound(int i)
{
	if (time(NULL) - g_all.sound > 3)
	{
		if (i == 1)
			system("afplay sound/Ta_da.mp3 &");
		if (i == 2)
			system("afplay sound/power_off.mp3 &");
		time(&g_all.sound);
	}
	return (0);
}

int		dump_memory(void)
{
	int		i;
	char	*buffer;
	char	*s;

	if (!(s = malloc((MEM_SIZE * 3) + 576)))
		exit_func(MERROR, 0);
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!i || !(i % 64))
		{
			if ((ft_printf("%.4p : %#>", i, &buffer) == -1))
				exit_func(MERROR, 0);
			ft_memcpy((s + (i / 64) * 9 + i * 3), buffer, 9);
			free(buffer);
		}
		if (ft_printf(CHAR_HEX_PRINT "%c%#>", g_all.arena[i], (i + 1) % 64 ? ' ' : '\n', &buffer) == -1)
			exit_func(MERROR, 0);
		ft_memcpy(s + (i / 64) * 9 + 9 + i * 3, buffer, 3);
		free(buffer);
	}
	write(1, s, (MEM_SIZE * 3) + 576);
	free(s);
	return (0);
}

int		update_cps(void)
{
	char	*tmp;

	if (ft_printf("%*d%#>", NUMBER_WIDTH, g_all.visu.max_cps, &tmp) == -1)
		exit_func(MERROR, 0);
	add_str_to_buffer(g_all.visu.next_frame + (3 + HEADER_HEIGHT) * g_all.visu.nb_cols - INFO_WIDTH + 25, tmp, WHITE, 0);
	insta_print_string(tmp, WHITE, 0, (3 + HEADER_HEIGHT) * g_all.visu.nb_cols - INFO_WIDTH + 25);
	free(tmp);
	return (0);
}
