/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square_rec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 07:57:07 by nabih             #+#    #+#             */
/*   Updated: 2019/12/08 08:03:03 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_square_rec(unsigned int nb, unsigned int pow)
{
	if (nb == 0)
		return (0);
	else if (pow == 0)
		return (1);
	else if (pow == 1)
		return (nb);
	return (nb * ft_square_rec(nb, pow - 1));
}
