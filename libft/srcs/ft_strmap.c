/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:29:36 by naali             #+#    #+#             */
/*   Updated: 2019/07/24 19:23:20 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char			*r;
	unsigned int	i;

	i = 0;
	r = NULL;
	if (s != NULL && f != NULL)
	{
		if ((r = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
			return (NULL);
		while (s[i] != '\0')
		{
			r[i] = (*f)(s[i]);
			i = i + 1;
		}
		r[i] = '\0';
	}
	return (r);
}
