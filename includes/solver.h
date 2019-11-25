/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:50:43 by nabih             #+#    #+#             */
/*   Updated: 2019/11/25 19:52:46 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		SOLVER_H
# define	SOLVER_H

# include "get_info.h"

typedef struct			s_flow
{
	uint32_t		now;
	uint32_t		start;
	uint32_t		end;
	uint32_t		flow_max;
}						t_flow;

int8_t					solver(t_lemin *lem);

#endif
