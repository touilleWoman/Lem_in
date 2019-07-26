/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:57:08 by naali             #+#    #+#             */
/*   Updated: 2019/07/24 19:21:13 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cpy;
	unsigned char	conv;

	i = 0;
	cpy = (unsigned char*)s;
	conv = (unsigned char)c;
	while (i < n)
	{
		if (cpy[i] == conv)
			return (&cpy[i]);
		i = i + 1;
	}
	return (NULL);
}
