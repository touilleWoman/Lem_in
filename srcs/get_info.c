/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 08:23:51 by nabih             #+#    #+#             */
/*   Updated: 2019/11/24 15:03:48 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_info.h>

/*
** Recuperation
**    D'INFO
*/
int8_t					get_info(t_lemin *lem)
{
	int8_t			ret;

	if ((ret = get_nb_ants(lem)) > 0)
	{
		if ((ret = get_node(lem)) == LM_SUCCESS)
		{
			/* Recuperation des PATHS */
			print_tab(lem->tab, HASHCODE);
		}
		else
		{
			ft_memdel((void**)&(lem->line));
			clear_hashtab(lem);
			return (LM_ERROR);
		}
	}
	return ((ret > 0) ? LM_SUCCESS : LM_ERROR);
}
