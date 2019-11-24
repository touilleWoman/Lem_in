/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 08:23:51 by nabih             #+#    #+#             */
/*   Updated: 2019/11/23 12:04:50 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_info.h>

/*
** Recuperation du nombre
**      DE  FOURMIES
*/
int8_t					get_nb_ants(t_lemin *lem)
{
	lem->nb_ants = 0;
	if (get_next_line(0, &(lem->line)) == 1)
	{
		lem->nb_ants = ft_atoi(lem->line);
		ft_memdel((void**)&(lem->line));
	}
	printf("|NB FOURMIES = %d|\n", lem->nb_ants);
	return ((lem->nb_ants > 0) ? LM_SUCCESS : LM_ERROR);
}

/*
** Verifie la commande
*/
static int8_t			check_cmd(t_lemin *lem, char *line)
{
	static uint8_t	end = 0;
	static uint8_t	start = 0;

	if (line[0] != '#')
		return (LM_IGNORE);
	else
	{
		if (ft_strcmp(&(line[1]), "start") == 0)
		{
			start++;
			lem->isstart = 1;
			return ((start == 1) ? LM_IGNORE : LM_ERROR);
		}
		else if (ft_strcmp(&(line[1]), "end") == 0)
		{
			end++;
			lem->isend = 1;
			return ((end == 1) ? LM_IGNORE : LM_ERROR);
		}
	}
	return (LM_ERROR);
}

/*
** Verifie la ligne
**    recuperer
*/
static int8_t			check_line(t_lemin *lem, char *line)
{
	int32_t			i;

	i = 0;
	if (line[0] != '\0')
	{
		if (line[0] == '#')
			return (check_cmd(lem, &(line[1])));
		else
		{
			while (line[i] != '\0')
			{
				if (line[i] == '-')
					return (LM_STOP);
				else if (line[i] == ' ')
				{
					line[i] = '\0';
					return (LM_SUCCESS);
				}
				else if (ft_isalnum(line[i]) != 1)
					return (LM_ERROR);
				i++;
			}
		}
	}
	return (LM_ERROR);
}

static int8_t			create_n_add(t_lemin *lem)
{
	t_node			*tmp;

	if (node_exist(lem, lem->line) != LM_TRUE)
	{
		if (lem->isstart == 1 && lem->isend == 1)
			return (LM_ERROR);
		tmp = new_node(lem->line, lem->isstart, lem->isend);
		add_node_in_tab(lem, tmp);
		if (lem->isstart == 1)
			lem->start = ft_strdup(lem->line);
		else if (lem->isend == 1)
			lem->end = ft_strdup(lem->line);
		lem->isstart = 0;
		lem->isend = 0;
		printf("SUCCESS: %s\n", lem->line);
	}
	else
		return (LM_ERROR);
	return (LM_SUCCESS);
}

/*
** Recuperation
**  DES NOEUDS
*/
int8_t					get_node(t_lemin *lem)
{
	int8_t			ret;

	lem->end = NULL;
	lem->start = NULL;
	while (get_next_line(0, &(lem->line)) == LM_SUCCESS
			&& ((ret = check_line(lem, lem->line)) == LM_SUCCESS\
				|| ret == LM_IGNORE))
	{
		if (ret != LM_IGNORE && ret != LM_STOP)
		{
			if (create_n_add(lem) != LM_SUCCESS)
				return (LM_ERROR);
		}
		ft_memdel((void**)&(lem->line));
	}
	ft_memdel((void**)&(lem->line));
	if (lem->start == NULL || lem->end == NULL)
		return (LM_ERROR);
	return ((ret == LM_STOP) ? LM_SUCCESS : LM_ERROR);
}

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
