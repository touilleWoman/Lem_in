/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:48:42 by nabih             #+#    #+#             */
/*   Updated: 2019/11/23 11:51:54 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <get_info.h>

int				main()
{
	t_lemin		lem;
	/* t_node		*tmp; */

	if (HASHCODE > 100 && HASHCODE < 50000)
	{
		lem.line = NULL;
		ft_bzero(lem.tab, sizeof(t_node*) * HASHCODE);
		if (get_info(&lem) == LM_SUCCESS)
			printf("start solver\n");
		else
			printf("An error occured\n");
		/* if (ac >= 2 && HASHCODE > 10) */
		/* { */
		/* 	while (i < (uint32_t)ac && flg == LM_FALSE) */
		/* 	{ */
		/* 		if ((flg = node_exist(&lem, av[i])) == LM_FALSE) */
		/* 		{ */
		/* 			if ((tmp = new_node(av[i], LM_FALSE, LM_FALSE)) == NULL) */
		/* 			{ */
		/* 				printf("Node Creation Failure\n"); */
		/* 				clear_hashtab(&lem); */
		/* 				flg = LM_TRUE; */
		/* 			} */
		/* 			else */
		/* 				add_node_in_tab(&lem, tmp); */
		/* 		} */
		/* 		else */
		/* 		{ */
		/* 			printf("Erreur doublon [%s]\n", av[i]); */
		/* 			clear_hashtab(&lem); */
		/* 		} */
		/* 		i++; */
		/* 	} */
		/* 	print_tab(lem.tab, HASHCODE); */
		/* 	clear_hashtab(&lem); */
		/* } */
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
				printf("|[%d] ==> %s (Entree:%s) (Sortie:%s)|", i, tmp->name, (tmp->start == 1) ? "oui" : "non", (tmp->end == 1) ? "oui" : "non");
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
