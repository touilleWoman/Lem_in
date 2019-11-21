/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:48:42 by nabih             #+#    #+#             */
/*   Updated: 2019/11/21 19:25:46 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_list_id(t_path **test)
{
	t_path	*tmp;

	if (test != NULL)
	{
		tmp = *test;
		while (tmp != NULL)
		{
			printf("id noeud = %d a l'adress %p\n", tmp->id, tmp);
			tmp = tmp->next;
		}
		if (*test != NULL)
			ft_putchar('\n');
	}
}

int			main(int ac, char **av)
{
	t_path		*test;
	t_path		*dst;
	uint32_t	i;
	uint32_t	max;

	i = 0;
	test = NULL;
	dst = NULL;
	if (ac < 2)
		return (0);
	max = atoi(av[1]);
	while (i < max)
	{
		pushback_path(&test, new_path());
		i++;
	}

	print_list_id(&test);
	printf("nb path == %u\n\n", count_path(test));

	if (ac >= 3)
	{
		i = 2;
		while (i < (uint32_t)ac)
		{
			send_path_away(&test, &dst, atoi(av[i]));
			i++;
		}
	}

	print_list_id(&test);
	printf("nb path == %u\n\n", count_path(test));
	print_list_id(&dst);
	printf("nb path == %u\n", count_path(dst));

	printf("src = %p\ndst = %p\n", test, dst);
	clear_path(&test);
	clear_path(&dst);

	return (0);
}
