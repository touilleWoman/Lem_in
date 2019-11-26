/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:50:43 by nabih             #+#    #+#             */
/*   Updated: 2019/11/26 15:48:42 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		SOLVER_H
# define	SOLVER_H

# include "get_info.h"

typedef struct s_solver	t_solver;

struct					s_solver
{
	uint32_t		nb_node;
	t_node			*op_lst;
	t_node			*cl_lst;
	t_solver		*next;
};

int8_t					solver(t_lemin *lem);

#endif
