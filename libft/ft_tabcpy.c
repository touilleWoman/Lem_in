/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:54:48 by nabih             #+#    #+#             */
/*   Updated: 2019/11/07 14:21:59 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_tabcpy(char **dst, const char **src, unsigned int max)
{
	unsigned int	i;

	i = 0;
	while (i < max)
	{
		ft_strcpy(dst[i], src[i]);
		i = i + 1;
	}
	return (dst);
}
