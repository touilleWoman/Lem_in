/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_encryption.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:00:17 by nabih             #+#    #+#             */
/*   Updated: 2019/12/08 06:18:53 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Hashage du
** nom de noeud
*/
int32_t				hash_name(char *name)
{
	int32_t		i;
	int32_t		ret;
	int32_t		mult;

	ret = 0;
	if (name != NULL)
	{
		i = 0;
		mult = 1;
		while (name[i] != '\0')
		{
			if (ft_isalnum(name[i]) != 1 && name[i] != '_')
				return (LM_ERROR);
			ret += name[i] * mult;
			mult++;
			i++;
		}
	}
	else
		return (LM_ERROR);
	return (ret % HASHCODE);
}
