/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_encryption.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:00:17 by nabih             #+#    #+#             */
/*   Updated: 2019/11/22 20:14:23 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Hashage du
** nom de noeud
*/
int32_t		hash_name(char *name)
{
	int32_t	i;
	int32_t	ret;
	int32_t	mult;

	i = 0;
	ret = 0;
	mult = 1;
	if (name != NULL)
	{
		while (name[i] != '\0')
		{
			ret += name[i] * mult;
			mult++;
			i++;
		}
	}
	else
		return (LM_ERROR);
	return (ret % HASHCODE);
}
