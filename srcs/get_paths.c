/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:48:44 by nabih             #+#    #+#             */
/*   Updated: 2019/11/27 04:45:18 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_info.h>

static int8_t			check_for_valide_path(t_lemin *lem, char *line)
{
	t_node			*tmp;

	lem->dash = 0;
	while (line[lem->dash] != '-')
		(lem->dash)++;
	line[lem->dash] = '\0';
	if (ft_strcmp(line, &(line[lem->dash + 1])) == 0)
		return (LM_ERROR);
	if ((tmp = get_node_in_hash(lem, line)) != NULL)
	{
		tmp->nb_paths += 1;
		if ((tmp = get_node_in_hash(lem, &(line[lem->dash + 1]))) != NULL)
		{
			tmp->nb_paths += 1;
			return (LM_SUCCESS);
		}
	}
	return (LM_ERROR);
}

static int8_t			check_line(char *line)
{
	int32_t			i;
	int32_t			nb_dash;

	i = 0;
	nb_dash = 0;
	if (line[i] != '\0')
	{
		if (line[0] == '#')
			return ((line[1] != '#') ? LM_IGNORE : LM_ERROR);
		else
		{
			while (line[i] != '\0')
			{
				if (line[i] == '-' && i > 0)
					nb_dash++;
				else if (ft_isalnum(line[i]) != 1)
					return (LM_ERROR);
				if (nb_dash > 1)
					return (LM_ERROR);
				i++;
			}
		}
	}
	return ((nb_dash == 1) ? LM_SUCCESS : LM_ERROR);
}

/*
** Recuperation
**  DES  PATHS
*/
static int8_t			add_path(t_lemin *lem)
{
	t_node			*tmp;
	t_path			*tmp1;
	t_path			*tmp2;

	if ((tmp1 = new_path(lem->line, &(lem->line)[lem->dash + 1])) == NULL
		|| (tmp2 = copy_path(tmp1)) == NULL)
		return (LM_ERROR);
	tmp = get_node_in_hash(lem, tmp1->name[0]);
	pushfront_path(&(tmp->path_lst), tmp1);
	tmp = get_node_in_hash(lem, tmp2->name[0]);
	pushfront_path(&(tmp->path_lst), tmp2);
	/* if (ft_strcmp(tmp->name[0], lem->start) == 0 */
	/* 	|| ft_strcmp(tmp->name[1], lem->start) == 0) */
	/* 	add_path_at_id(lem, tmp, 0); */
	/* else if (ft_strcmp(tmp->name[0], lem->end) == 0 */
	/* 		 || ft_strcmp(tmp->name[1], lem->end) == 0) */
	/* 	add_path_at_id(lem, tmp, HASHCODE - 1); */
	/* else */
	/* 	add_path_at_id(lem, tmp, HASHCODE - 2);//Cette ligne est a changer pour permettre une meilleure repartition des pipes */
	return (LM_SUCCESS);
}

int8_t					get_path(t_lemin *lem)
{
	t_path			*tmp;
	int8_t			ret;

	tmp = NULL;
	lem->nb_paths = 0;
	printf("Last line get: |%s|\n", lem->line);
	while ((lem->line != NULL || get_next_line(0, &lem->line) == 1)
			&& (ret = check_line(lem->line)) != LM_ERROR)
	{
		if ((ret = check_for_valide_path(lem, lem->line)) == LM_ERROR)
			return (ret);
		if (add_path(lem) == LM_ERROR)
			return (LM_ERROR);
		lem->nb_paths += 1;
		ft_memdel((void**)&(lem->line));
	}
	ft_memdel((void**)&(lem->line));
	return (ret);
}

/*
  Information recuperer:
  - NB nodes
  - position du dash dans le nom
*/
/*
  CREATE and ADD path to hashtable
  Debut de reflexion:
  - Start a l'indice 0
  - End a l'indice HASHCODE - 1
  - Les autres a l'indice HASHCODE - 2
  - Si Start et/ou End == NULL => Resolution impossible
  - Partir de 0
  - Tester chaque path verifier la destination
  - Recuperer les paths de destination et les positionner a 2
  - Etc
*/
