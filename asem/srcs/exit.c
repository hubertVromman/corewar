/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:50:43 by hvromman          #+#    #+#             */
/*   Updated: 2019/04/12 16:50:44 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		free_instr(t_instr *current_instr)
{
	t_instr	*next_instr;

	while (current_instr)
	{
		next_instr = current_instr->next;
		for (int i = 0; i < 4; i++)
			if (&(current_instr->params[i]))
			{
				free(current_instr->params[i].data);
			}
		free(current_instr);
		current_instr = next_instr;
	}
	return (0);
}

int		free_file(t_file *file)
{
	t_label	*current_label;
	t_label	*next_label;

	free(file->header);
	free(file->cor_name);
	free(file->prog_name);
	free(file->prog_comment);
	free(file->prog_content);
	free(file->s_file_content);
	current_label = file->labels;
	while (current_label)
	{
		next_label = current_label->next;
		free(current_label->name);
		free(current_label);
		current_label = next_label;
	}
	free_instr(file->instr);
	return (0);
}

int		free_all(t_a *all)
{
	free(all->flags);
	return (0);
}

int		usage(void)
{
	ft_printf("usage: asm: [-%s] file.s ...\n%>", OP, 2);
	ft_printf("      -m  : Unable to compile multiple files\n%>", 2);
	return (0);
}

int		exit_func(int exit_code, int dp_usage, t_a *all)
{
	if (dp_usage)
		usage();
	if (!exit_code && all->nb_errors)
		exit_code = all->nb_errors;
	free_all(all);
	exit(exit_code);
}
