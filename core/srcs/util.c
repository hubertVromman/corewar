/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:16:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/27 05:18:42 by sofchami         ###   ########.fr       */
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

int		sort_proces(t_champ *champ)
{
	t_proces tmp;
	int		i;

	i = -1;
	while (++i < champ->nb_proces)
	{
		if (i + 1 < champ->nb_proces && champ->proces[i].id_proces > champ->proces[i + 1].id_proces)
		{
			tmp = champ->proces[i];
			champ->proces[i] = champ->proces[i + 1];
			champ->proces[i + 1] = tmp;
			i = -1;
		}
	}
	return (0);
}

int		play_sound(int i)
{
	i = 0;
	// system("pkill afplay &");
	// if (i == 1)
	// system("afplay sound/Ta_da.mp3 &");
	// if (i == 2)
	// system("afplay sound/power_off.mp3 &");
	return (0);
}

int		detele_proces(t_champ *champ, int id_proces)
{
	int		pos;
	char	*buf;

	if (g_all.flags[VISU])
	{
		buf = NULL;
		pos = jump_to_buf(champ->proces[id_proces].pc);
		ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[champ->proces[id_proces].pc], &buf);
		write_to_buffer(g_all.visu.next_frame + pos, buf[0], g_all.color[champ->proces[id_proces].pc], 0);
		write_to_buffer(g_all.visu.next_frame + pos + 1, buf[1], g_all.color[champ->proces[id_proces].pc], 0);
		free(buf);
	}
	ft_memcpy(&(champ->proces[id_proces]), &(champ->proces[id_proces + 1]), sizeof(t_proces) * (champ->nb_proces - 1 - id_proces));
	champ->nb_proces--;
	g_all.nb_proces_tot--;
	// sort_proces(champ);
	// play_sound(S_DEATH);
	return (0);
}

int		create_proces(int pc, t_proces *parent, t_champ *champ)
{
	t_proces *proc;

	if (!(champ->proces = realloc(champ->proces, sizeof(t_proces) * (champ->nb_proces + 1))))
		return (-1);
	proc = &(champ->proces[champ->nb_proces]);
	ft_bzero(proc, sizeof(t_proces));
	proc->pc = pc;
	proc->opcode = read_arena_op(proc->pc);
	proc->cycle_left = get_cycle_left(proc->opcode);
	proc->id_proces = g_all.id_proces;
	if (parent)
	{
		ft_memcpy(proc->reg, parent->reg, REG_NUMBER * 4);
		proc->carry = parent->carry;
	}
	else
		proc->reg[0] = champ->player_nb_arena;
	proc->champ = champ;
	proc->color_rgb = proc->champ->color_rgb + champ->nb_proces * COLOR_INCREMENT;
	if (champ->nb_proces)
		increment_pc(proc, 0);
	champ->nb_proces++;
	g_all.nb_proces_tot++;
	g_all.id_proces++;
	g_all.cycle ? play_sound(S_LIVE) :0;
	return(0);
}

int		dump_memory()
{
	int		i;
	char *buffer;
	char *s;

	if (!(s = malloc(MEM_SIZE * 3)))
		exit_func(MERROR, 0);
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (ft_printf(CHAR_HEX_PRINT "%c%#>", g_all.arena[i], (i + 1) % 64 ? ' ' : '\n', &buffer) == -1)
			exit_func(MERROR, 0);
		memcpy(s + i * 3, buffer, 3);
		free(buffer);
	}
	write(1, s, MEM_SIZE * 3);
	free(s);
	return (0);
}

int		fill_current_frame()
{
	char *tmp;

	tmp = NULL;
	print_border();
	print_header();
	if (ft_printf("%1$/43c Info %1$/43c %#>", '-', &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + (HEADER_HEIGHT * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	if (ft_printf("Cycles %#>", &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 1) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	if (ft_printf("Cycles/second limit %#>", &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 2) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	if (ft_printf("Nbr de proces %#>", &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 3) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	if (ft_printf("Lives period %#>", &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 4) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	if (ft_printf("Cycle to die %#>", &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 5) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);

	for(int i = 0; i < g_all.nb_champ; i++)
	{
		if (ft_printf("PLAYER %d : %#>", g_all.champ[i].player_nb, &tmp) == -1)
			exit_func(MERROR, 0);
		add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 7 + (i < 2 ? (i * 5) : (i - 2) * 5)) * g_all.visu.nb_cols + (i < 2 ? X : (X + 50))), tmp, 0x00ffffff, 0);
		free(tmp);
		if (ft_printf("%s %#>", g_all.champ[i].player_name, &tmp) == -1)
			exit_func(MERROR, 0);
		add_name_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 7 + (i < 2 ? (i * 5) : (i - 2) * 5)) * g_all.visu.nb_cols + (i < 2 ? X + 12 : X + 62)), tmp, g_all.champ[i].color_rgb, 0);
		free(tmp);
		if (ft_printf("Last lives %#>", &tmp) == -1)
			exit_func(MERROR, 0);
		add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 8 + (i < 2 ? (i * 5) : (i - 2) * 5)) * g_all.visu.nb_cols + (i < 2 ? X + 5 : X + 55)), tmp, 0x00ffffff, 0);
		free(tmp);
		if (ft_printf("Lives period %#>", &tmp) == -1)
			exit_func(MERROR, 0);
		add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 9 + (i < 2 ? (i * 5) : (i - 2) * 5)) * g_all.visu.nb_cols + (i < 2 ? X + 5 : X + 55)), tmp, 0x00ffffff, 0);
		free(tmp);
		if (ft_printf("Nbr of proces %#>", &tmp) == -1)
			exit_func(MERROR, 0);
		add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 10 + (i < 2 ? (i * 5) : (i - 2) * 5)) * g_all.visu.nb_cols + (i < 2 ? X + 5 : X + 55)), tmp, 0x00ffffff, 0);
		free(tmp);
	}

	if (ft_printf("%1$/40c ALL proces %1$/40c %#>", '-', &tmp) == -1)
		exit_func(MERROR, 0);
	add_string_to_buffer(g_all.visu.current_frame + ((HEADER_HEIGHT + 18) * g_all.visu.nb_cols + X), tmp, 0x00ffffff, 0);
	free(tmp);
	return (0);
}

int		init_current_frame()
{
	int i;
	int p;
	int pos;
	char *buf = NULL;

	i = -1;
	p = 0;
	while (++i < MEM_SIZE)
	{
		pos = jump_to_buf(i);
		if (i >= g_all.champ[p].proces->pc && i < (g_all.champ[p].proces->pc + g_all.champ[p].exec_size))
		{
			ft_printf(CHAR_HEX_PRINT "%#>", g_all.arena[i], &buf);
			write_to_buffer(g_all.visu.current_frame + pos, buf[0], g_all.champ[p].proces->color_rgb, 0);
			write_to_buffer(g_all.visu.current_frame + pos + 1, buf[1], g_all.champ[p].proces->color_rgb, 0);
			write_to_buffer(g_all.visu.current_frame + pos + 2, ' ', g_all.champ[p].proces->color_rgb, 0);
		}
		else
		{
			write_to_buffer(g_all.visu.current_frame + pos, '0', VM_COLOR, 0);
			write_to_buffer(g_all.visu.current_frame + pos + 1, '0', VM_COLOR, 0);
			write_to_buffer(g_all.visu.current_frame + pos + 2, ' ', VM_COLOR, 0);
		}
		if (p < (g_all.nb_champ - 1) && i + 1 == g_all.champ[p + 1].proces->pc)
			p++;
	}
	fill_current_frame();
	for (int j = 0; j < g_all.nb_champ; j++)
	{
		pos = jump_to_buf(g_all.champ[j].proces->pc);
		int tmp = g_all.visu.current_frame[pos].fore_color;
		g_all.visu.current_frame[pos].fore_color = g_all.visu.current_frame[pos].back_color;
		g_all.visu.current_frame[pos].back_color = tmp;
		pos++;
		tmp = g_all.visu.current_frame[pos].fore_color;
		g_all.visu.current_frame[pos].fore_color = g_all.visu.current_frame[pos].back_color;
		g_all.visu.current_frame[pos].back_color = tmp;
	}
	ft_memcpy(g_all.visu.current_frame_flame, g_all.visu.current_frame, g_all.visu.screen_size);
	for (int j = 0 ; j < g_all.visu.screen_size; j++)
	{
		if (g_all.visu.current_frame[j].to_print)
		{
			print_char(g_all.visu.current_frame[j], j);
		}
	}
	return (0);
}
