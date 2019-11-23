/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:48:42 by nabih             #+#    #+#             */
/*   Updated: 2019/11/23 04:00:49 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int				main(int ac, char **av)
{
	uint32_t	i;
	t_lemin		lem;
	uint8_t		flg;

	i = 1;
	flg = LM_FALSE;
	ft_bzero(lem.tab, sizeof(t_node*) * HASHCODE);
	if (ac >= 2 && HASHCODE > 10)
	{
		while (i < (uint32_t)ac && flg == LM_FALSE)
		{
			if ((flg = node_exist(&lem, av[i])) == LM_FALSE)
				add_node_in_tab(&lem, new_node(av[i], LM_FALSE, LM_FALSE));
			else
			{
				printf("Erreur doublon [%s]\n", av[i]);
				clear_hashtab(&lem);
			}
			i++;
		}
		print_tab(lem.tab, HASHCODE);
	}
	return (0);
}

/*
** Test d'affichage
*/
void			print_tab(t_node *(tab)[HASHCODE], uint32_t max)
{
	t_node		*tmp;
	uint32_t	i;

	i = 0;
	while (i < max)
	{
		if (tab[i] != NULL)
		{
			tmp = tab[i];
			while (tmp != NULL)
			{
				printf("|[%d] ==> %s|", i, tmp->name);
				if (tmp->next != NULL)
					printf(" ");
				tmp = tmp->next;
			}
			printf("\n");
		}
		i++;
	}
}
/* Fin de TEST */
