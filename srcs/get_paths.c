/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:48:44 by nabih             #+#    #+#             */
/*   Updated: 2019/11/29 20:49:18 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_info.h>

static uint8_t			check_existing_path(t_lemin *lem, char *line, t_node *n)
{
	t_path			*tmp;

	tmp = n->path_lst;
	if (tmp != NULL)
	{
		while (tmp != NULL)
		{
			if (ft_strcmp(&(line[lem->dash + 1]), tmp->name[1]) == 0)
				return (LM_TRUE);
			tmp = tmp->next;
		}
	}
	return (LM_FALSE);
}

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
		if (check_existing_path(lem, line, tmp) == LM_TRUE)
			return (LM_IGNORE);
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
	// t_node			*tmp;
	t_path			*path1;
	t_path			*path2;
	t_node			*node1;
	t_node			*node2;

	node1 = get_node_in_hash(lem, lem->line);
	node2 = get_node_in_hash(lem, &(lem->line)[lem->dash + 1]);
	// if ((tmp1 = new_path(lem->line, &(lem->line)[lem->dash + 1])) == NULL
		// || (tmp2 = copy_path(tmp1)) == NULL)
	// 	return (LM_ERROR);
	if ((path1 = new_path(node1->unid, node1->name)) == NULL
		|| (path2 = new_path(node2->unid, node2->name)) == NULL)
		return (LM_ERROR);
	// tmp = get_node_in_hash(lem, tmp1->name[0]);
	// pushfront_path(&(tmp->path_lst), tmp1);
	pushfront_path(&(node1->path_lst), path2);
	// tmp = get_node_in_hash(lem, tmp2->name[0]);
	// pushfront_path(&(tmp->path_lst), tmp2);
	pushfront_path(&(node2->path_lst), path1);
	return (LM_SUCCESS);
}

int8_t					get_path(t_lemin *lem)
{
	t_path			*tmp;
	int8_t			ret;

	tmp = NULL;
	lem->nb_paths = 0;
	while ((lem->line != NULL || get_next_line(0, &lem->line) == 1)
			&& (ret = check_line(lem->line)) != LM_ERROR)
	{
		if ((ret = check_for_valide_path(lem, lem->line)) == LM_ERROR)
			return (ret);
		if (ret == LM_SUCCESS)
		{
			if (add_path(lem) == LM_ERROR)
				return (LM_ERROR);
			lem->nb_paths += 1;
		}
		ft_memdel((void**)&(lem->line));
	}
	ft_memdel((void**)&(lem->line));
	return ((ret != LM_ERROR) ? LM_SUCCESS : LM_ERROR);
}
