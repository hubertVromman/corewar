/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:28:49 by hvromman          #+#    #+#             */
/*   Updated: 2019/08/31 03:06:21 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** TO DO or !Not to do
** - Dans create proces lecture des OP de la Queu et zjmp ?
** - recheck l'asm
** 				20/26
**
** PIPELINE
** - Norme
** - Gerer son
** - afficher indicateur pour "Pause" --> utiliser print char a la place de printf PUIS OK
** - Information alignees a droite --> ok mais changer dans print info et printinfo au demarrage
** - Verifier qu'on kill les thread --> ok jusqu'au prochain double free / heap use after free / etc
**
** DEJA FAIT
** - Why else dans le lecteur ? --> ok
** - Remplacer printf dans visu par insta_print_char --> ok
** 	 Gagnant qui bouge dans l'ecran (avec une couleur random ?) --> ok un peu bcp random
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

int		parse_arg(int ac, char **av)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
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
				j = 0;
				while (av[i][++j])
				{
					if ((k = ft_indexof(OP, av[i][j])) == -1)
						exit_func(-1, 1);
					g_all.flags[k] = 1;
				}
			}
		}
		else
		{
			get_champ(av[i]);
			g_all.nb_champ++;
		}
	}
	return (0);
}

int		display_start()
{
	int		i;

	if (g_all.flags[VISU])
	{
		if (g_all.visu.nb_cols < SCREEN_WIDTH || g_all.visu.nb_lines < SCREEN_HEIGHT - 1)
			exit_func(-1, 1);
		ft_printf(HIDE_CURSOR SAVE_SCREEN HOME_CURSOR);
		init_current_frame();
	}
	else
	{
		ft_printf("%s\n", "Introducing contestants...");
		i = -1;
		while (++i < g_all.nb_champ)
		{
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", g_all.champ[i].player_nb, g_all.champ[i].exec_size, g_all.champ[i].player_name, g_all.champ[i].comment);
		}
	}
	return (0);
}

int		main(int ac, char **av)
{
	init_all(ac, av);
	display_start();
	beg_battle();
	exit_func(0, 0);
}
