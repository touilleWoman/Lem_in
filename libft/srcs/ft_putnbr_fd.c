/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:17:16 by naali             #+#    #+#             */
/*   Updated: 2019/07/24 19:22:06 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	int		cp;
	int		mod;

	mod = 1;
	if (n >= 0)
		n = n * (-1);
	else
		ft_putchar_fd('-', fd);
	cp = n;
	while (cp < -9)
	{
		cp = cp / 10;
		mod = mod * 10;
	}
	while (mod > 0)
	{
		ft_putchar_fd('0' + ((n / mod) * -1), fd);
		n = n % mod;
		mod = mod / 10;
	}
}
