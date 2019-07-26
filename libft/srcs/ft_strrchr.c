/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:00:39 by naali             #+#    #+#             */
/*   Updated: 2019/07/24 19:23:59 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrchr(const char *s, int c)
{
	char		*cpy;
	char		conv;

	conv = (char)c;
	cpy = (char*)s;
	while (*cpy != '\0')
		cpy = cpy + 1;
	while (cpy != s)
	{
		if (*cpy == conv)
			return (cpy);
		cpy = cpy - 1;
	}
	if (*cpy == conv)
		return (cpy);
	return (NULL);
}
