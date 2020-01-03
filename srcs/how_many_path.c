/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:27:59 by nabih             #+#    #+#             */
/*   Updated: 2020/01/03 15:51:46 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <solver.h>
#include <get_many_path.h>

uint32_t				*init_ants_tab(uint32_t *tab, uint32_t len)
{
	if (!(tab = malloc(sizeof(uint32_t) * (len + 1))))
		return (NULL);
	while (len > 0)
		tab[len--] = 0;
	tab[len] = 0;
	return (tab);
}

static uint32_t			init_max(t_circuits **c, uint32_t len, uint32_t ants)
{
	uint32_t		i;
	uint32_t		max;

	i = 0;
	max = get_appro_max(c, len, ants);
	while (c[i]->nb_floor < max && i < len)
		i++;
	return (i);
}

static void				fill_ant_tab(uint32_t **tab, uint32_t len,
										uint32_t ants)
{
	uint32_t		i;

	i = 0;
	while (ants > 0)
	{
		i = 0;
		while (i < len && ants > 0)
		{
			(*tab)[i] += 1;
			ants--;
			i++;
		}
	}
}

static uint32_t			*ants_spreading(t_circuits **c, uint32_t *tab,
										uint32_t len, uint32_t ants)
{
	uint32_t		i;
	uint32_t		j;
	uint32_t		max;

	i = 0;
	max = init_max(c, len, ants);
	while (i < len && ants > 0)
	{
		j = 0;
		while ((c[j]->nb_floor + tab[j]) < (c[i]->nb_floor + tab[i])
				&& ants > 0 && i < max)
		{
			j = 0;
			while (j < i && ants > 0)
			{
				tab[j++] += 1;
				ants--;
			}
			j--;
		}
		i++;
		max++;
	}
	fill_ant_tab(&tab, len, ants);
	return (tab);
}

uint32_t				how_many_path(t_circuits **c, uint32_t len,
										uint32_t ants)
{
	static uint32_t		enter = 0;
	static uint32_t		*ants_tab = NULL;
	uint32_t			i;

	i = 0;
	enter++;
	if (enter == 1)
	{
		if ((ants_tab = init_ants_tab(ants_tab, len)) == NULL)
			return (-1);
		ants_tab = ants_spreading(c, ants_tab, len, ants);
	}
	while (i < len && ants_tab[i] > 0)
	{
		ants_tab[i] -= 1;
		i++;
	}
	if (ants_tab != NULL && ants_tab[0] == 0)
		ft_memdel((void**)&ants_tab);
	return (i);
}
