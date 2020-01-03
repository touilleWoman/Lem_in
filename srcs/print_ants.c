/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:45:26 by jleblond          #+#    #+#             */
/*   Updated: 2020/01/03 15:25:38 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

/*
** Attribut les chemins au fourmies qui entre dans
** la fourmilliere. Avant d'entrer leur PATH est
** initialiser a NULL.
*/

static void				init_ant_cir(t_circuits **c, t_list **ants, int32_t nb)
{
	int32_t			i;
	t_list			*tmp;

	i = 0;
	if (c && *c && ants && *ants && nb > 0)
	{
		tmp = *ants;
		while (tmp->content)
			tmp = tmp->next;
		while (i < nb && tmp)
		{
			tmp->content = (void*)(c[i]->addr)->next;
			tmp = tmp->next;
			i++;
		}
	}
}

/*
** Affiche une seul fourmie
*/

static void				print_one_ant(uint32_t ant_index, char *node_name)
{
	ft_putchar('L');
	ft_putnbr(ant_index);
	ft_putchar('-');
	ft_putstr(node_name);
}

/*
** Affiche une ligne complete en se basant sur les
** chemins stocker dans les noeuds des fourmies.
** si une fourmies arrive en fin de chemin son
** noeud est automatiquement liberer.
*/

static int32_t			print_line(t_list **ants, int32_t nb)
{
	int32_t			end;
	size_t			cs;
	t_list			*tmp;
	t_list			*cp;
	t_node			*node;

	end = 0;
	tmp = *ants;
	while (nb > 0 && tmp)
	{
		cp = (t_list*)(tmp->content);
		node = *(t_node**)(cp->content);
		print_one_ant(tmp->content_size, node->name);
		cs = tmp->content_size;
		cp = cp->next;
		tmp->content = (void*)cp;
		tmp = tmp->next;
		if (cp == NULL)
		{
			ft_lstdel_contentsize(ants, cs);
			++end;
		}
		(--nb > 0) ? ft_putchar(' ') : 0;
	}
	return (end);
}

/*
** Selectionne les chemins et les attribut a chaque
** fourmies au fur et a mesure qu'elles sont selectionner
** pour entrer dans la fourmilliere
** Affiche ligne par ligne les etapes.
*/

void					print_ants(t_lemin *lem, t_list **ants,
									t_circuits **cir_tab, int32_t tab_len)
{
	int32_t			send;
	int32_t			total_enter;
	int32_t			total_exit;

	total_enter = 0;
	total_exit = 0;
	while (ants && *ants)
	{
		send = 0;
		if (lem->nb_ants - total_enter > 0)
		{
			send = how_many_path(cir_tab, tab_len, lem->nb_ants - total_enter);
			if (send == -1)
				return ;
			init_ant_cir(cir_tab, ants, send);
			total_enter += send;
		}
		total_exit += print_line(ants, total_enter - total_exit);
		ft_putchar('\n');
	}
}
