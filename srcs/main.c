/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:48:42 by nabih             #+#    #+#             */
/*   Updated: 2019/11/30 21:20:48 by nabih            ###   ########.fr       */
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
		if (get_info(&lem) == LM_SUCCESS)
		{
			print_tab(lem.tab, HASHCODE);// A DELETE
			/* print_info_inout(&lem);// A DELETE */
			ft_putstr("start solver\n");
			solver(&lem);
		}
		else
			ft_putstr("An error occured\n");
		clear_hashtab(&lem);
	}
	return (0);
}

/*
** Test d'affichage
*/
void			print_info_inout(t_lemin *lem)
{
	ft_putstr("NB Fourmies = ");
	ft_putnbr(lem->nb_ants);
	ft_putchar('\n');
	ft_putstr("NB nodes = ");
	ft_putnbr(lem->nb_nodes);
	ft_putchar('\n');
	ft_putstr("NB paths = ");
	ft_putnbr(lem->nb_paths);
	ft_putchar('\n');
	ft_putstr("Entrer = ");
	ft_putstr(lem->start->name);
	ft_putchar('\n');
	ft_putstr("Sortie = ");
	ft_putstr(lem->end->name);
	ft_putchar('\n');
}

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
				printf("|unid[%d]id[%d] ==> %s (nb_paths:%d)|", tmp->unid, i, tmp->name,
						 tmp->nb_paths);
				printf("=PATH=>");
				print_pth(&(tmp->path_lst));
				if (tmp->next != NULL)
					printf(" ");
				tmp = tmp->next;
			}
			printf("\n");
		}
		i++;
	}
}

void			print_pth(t_path **tab)
{
	t_path		*tmp;
	uint32_t	i;

	i = 0;
	tmp = *tab;
	while (tmp != NULL)
	{
		printf("[%s]", tmp->name);
		if (tmp->next != NULL)
			printf(" ");
		tmp = tmp->next;
	}
}
/* Fin de TEST */
