/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:48:42 by nabih             #+#    #+#             */
/*   Updated: 2019/11/24 14:55:30 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <get_info.h>

int				main()
{
	t_lemin		lem;

	if (HASHCODE > 100 && HASHCODE < 50000)
	{
		lem.line = NULL;
		ft_bzero(lem.tab, sizeof(t_node*) * HASHCODE);
		ft_bzero(lem.pth, sizeof(t_node*) * HASHCODE);
		if (get_info(&lem) == LM_SUCCESS)
		{
			ft_putstr(lem.start);
			ft_putchar('\n');
			ft_putstr(lem.end);
			ft_putchar('\n');
			printf("start solver\n");
		}
		else
			printf("An error occured\n");
		clear_hashtab(&lem);
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
				printf("|[%d] ==> %s (Entree:%s) (Sortie:%s)|", i, tmp->name,
						(tmp->start == 1) ? "oui" : "non",
							(tmp->end == 1) ? "oui" : "non");
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
