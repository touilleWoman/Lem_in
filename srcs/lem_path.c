/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 01:02:30 by nabih             #+#    #+#             */
/*   Updated: 2019/11/25 01:38:24 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Ajoute un element
** au tableau de hash
*/
void					add_path_at_id(t_lemin *lem, t_path *pth, uint32_t id)
{
	if (pth != NULL && id < HASHCODE)
		pushfront_path(&(lem->pth[id]), pth);
}

/*
** Vide le tableau
** et free les espaces
*/
void					clear_hashpth(t_lemin *lem)
{
	uint32_t		i;

	i = 0;
	while (i < HASHCODE)
	{
		if ((lem->pth)[i] != NULL)
			clear_path(&((lem->pth)[i]));
		i++;
	}
}
