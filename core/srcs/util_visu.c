/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 03:11:00 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/20 20:36:54 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		write_to_buf(t_printable *strct, char c, int f_color, int b_color)
{
	strct->to_print = c;
	strct->fore_color = f_color & 0xffffff;
	strct->back_color = b_color & 0xffffff;
	return (0);
}

int		add_str_to_buf(t_printable *strct, char *str, int f_color, int b_color)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		write_to_buf(strct + i, str[i], f_color, b_color);
	}
	return (0);
}

int		add_name_to_buf(t_printable *strct, char *str, int f_color, int b_color)
{
	int		i;

	i = -1;
	while (str[++i] && i < MAX_NAME_LENGTH)
	{
		write_to_buf(strct + i, str[i], f_color, b_color);
	}
	return (0);
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

int		update_cps(void)
{
	char	*tmp;
	char	*s;
	int		pos;

	if (g_all.pause_changed)
	{
		if (g_all.visu.pause)
			s = "Pause  ";
		else
			s = "Running";
		pos = g_all.visu.nb_cols * 6 + 5;
		add_str_to_buf(g_all.visu.next_frame + pos, s, WHITE, 0);
		insta_print_string(s, WHITE, 0, pos);
		g_all.pause_changed = 0;
	}
	if (ft_printf("%*d%#>", NUM_WIDTH, g_all.visu.max_cps, &tmp) == -1)
		exit_func(MERROR, 0);
	pos = (4 + HEADER_HEIGHT) * g_all.visu.nb_cols - INFO_WIDTH + 26;
	add_str_to_buf(g_all.visu.next_frame + pos, tmp, WHITE, 0);
	insta_print_string(tmp, WHITE, 0, pos);
	free(tmp);
	return (0);
}
