/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:24:41 by mbourand          #+#    #+#             */
/*   Updated: 2019/11/19 09:25:25 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	ft_putunsignednbr_fd(unsigned int n, int fd)
{
	char	c;

	if (n >= 10)
		ft_putunsignednbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}
