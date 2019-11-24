/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:48:44 by nabih             #+#    #+#             */
/*   Updated: 2019/11/24 18:27:47 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_info.h>

static int8_t			check_for_valide_path(t_lemin *lem, char *line)
{
	t_node			*tmp;
	int				dash;

	dash = 0;
	while (line[dash] != '-')
		dash++;
	line[dash] = '\0';
	if (ft_strcmp(line, &(line[dash + 1])) == 0)
		return (LM_ERROR);
	if ((tmp = get_node_in_hash(lem, line)) != NULL)
	{
		tmp->nb_paths += 1;
		if ((tmp = get_node_in_hash(lem, &(line[dash + 1]))) != NULL)
		{
			line[dash] = '-';
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
int8_t					get_path(t_lemin *lem)
{
	int8_t			ret;

	lem->nb_paths = 0;
	printf("Last line get: |%s|\n", lem->line);
	while ((lem->line != NULL || get_next_line(0, &lem->line) == 1)
			&& (ret = check_line(lem->line)) != LM_ERROR)
	{
		if ((ret = check_for_valide_path(lem, lem->line)) == LM_ERROR)
			return (ret);
		lem->nb_paths += 1;
		ft_memdel((void**)&(lem->line));
	}
	ft_memdel((void**)&(lem->line));
	return (ret);
}
