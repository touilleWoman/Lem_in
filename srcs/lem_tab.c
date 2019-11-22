/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 23:19:25 by nabih             #+#    #+#             */
/*   Updated: 2019/11/22 23:21:50 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Ajoute un element
** au tableau de hash
*/
void			add_node_in_tab(t_lemin *lem, t_node *node)
{
	if (node != NULL && node->id < HASHCODE)
		pushfront_node(&(lem->tab[node->id]), node);
}
