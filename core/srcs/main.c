/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:28:49 by hvromman          #+#    #+#             */
/*   Updated: 2019/09/04 22:23:27 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** TO DO or !Not to do
** - recheck l'asm
** - toujours un soucis avec Gagnant.cor
** - io_arena a changer dans git
** - r19 ? increment arglen ?
** 				24/28
**
** PIPELINE
** - Norme
**
** DEJA FAIT
** 	 Gagnant qui bouge dans l'ecran (avec une couleur random ?) --> ok
** - Verifier qu'on kill les thread --> ok
** - afficher indicateur pour "Pause" --> ok
** - Information alignees a droite --> ok
** - Dans create proces lecture des OP de la Queu et zjmp --> ok
** - Gerer son --> ok
** - Why else dans le lecteur ? --> ok
** - Remplacer printf dans visu par insta_print_char --> ok
** - Verifier tout les printf pour affichage sans visu --> ok
** - Pas de visu si screen est trop petit --> ok
** - Nb du champion reste comme il est mais passe en neg dans le registre --> ok
** - Gerer la double impression au debut --> ok
** - Fonction AFF --> ok
** - flag i pour les lives et aff --> ok
** - Mettre tout dans le buffer "print info"   --> ok
** - tester dernier en vie  --> ok
** - sound flame on of quand il faut  -> ok
** - tout les 16 par des defines Nb_Operation --> ok
** - Bug affichage  --> ok
** - faire des define pour le son   --> ok
** - proteger les printfs qui mettent dans le buffer  --> ok
** - verifier tous les free --> ok
** - faire un print char pour afficher --> ok
** - error_func pour player nb a chequer --> ok
*/

int		check_normal_option(char **av, int i)
{
	int		j;
	int		k;

	j = 0;
	while (av[i][++j])
	{
		if ((k = ft_indexof(OP, av[i][j])) == -1)
			exit_func(-1, 1);
		g_all.flags[k] = 1;
	}
	return (0);
}

int		check_option(char **av, int ac, int i)
{
	if (!ft_strcmp(av[i] + 1, "n"))
	{
		if (i + 1 == ac)
			exit_func(-1, 1);
		if ((g_all.next_champ_nb = ft_atoi(av[++i])) <= 0)
		{
			error_func(NULL, INVALID_NB);
			g_all.next_champ_nb = 0;
		}
	}
	else if (!ft_strcmp(av[i] + 1, "dump"))
	{
		if (i + 1 == ac || g_all.dump_period)
			exit_func(-1, 1);
		g_all.dump_period = ft_atoi(av[++i]);
		if (g_all.dump_period < 1)
			exit_func(-1, 1);
	}
	else
	{
		check_normal_option(av, i);
	}
	return (i);
}

int		parse_arg(int ac, char **av)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			i = check_option(av, ac, i);
		}
		else
		{
			get_champ(av[i]);
			g_all.nb_champ++;
		}
	}
	return (0);
}

int		display_start(void)
{
	int		i;

	if (g_all.flags[VISU])
	{
		if (g_all.visu.nb_cols < SCREEN_WIDTH
			|| g_all.visu.nb_lines < SCREEN_HEIGHT - 1)
			exit_func(-1, 1);
		ft_printf(HIDE_CURSOR "" SAVE_SCREEN "" HOME_CURSOR);
		init_current_frame();
	}
	else
	{
		ft_printf("%s\n", "Introducing contestants...");
		i = -1;
		while (++i < g_all.nb_champ)
		{
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				g_all.champ[i].player_nb, g_all.champ[i].exec_size,
				g_all.champ[i].player_name, g_all.champ[i].comment);
		}
	}
	return (0);
}

int		main(int ac, char **av)
{
	init_all(ac, av, -1);
	display_start();
	beg_battle();
	exit_func(0, 0);
}
