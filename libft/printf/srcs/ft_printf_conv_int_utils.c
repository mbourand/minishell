/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_int_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:43:15 by nforay            #+#    #+#             */
/*   Updated: 2020/07/31 16:55:10 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		get_intlen(int n, int len)
{
	if (n == -2147483648)
		return (10);
	if (n <= 0)
		n = -n;
	while (n >= 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	ft_printf_int(int n, t_state_machine *m)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("214748364", m->fd);
		m->fwidth -= 9;
		m->len += 9;
		n = 8;
	}
	if (n <= 9 && n >= 0)
	{
		ft_putchar_fd(n + 48, m->fd);
		m->len++;
		m->fwidth--;
	}
	else
	{
		ft_printf_int(n / 10, m);
		ft_putchar_fd(n % 10 + 48, m->fd);
		m->len++;
		m->fwidth--;
	}
}

void	ft_printf_nbr_int_fd(int n, int size, t_state_machine *m)
{
	if (n < 0)
		n *= -1;
	while ((m->preci - size) > 0)
	{
		ft_putchar_fd('0', m->fd);
		m->len++;
		m->preci--;
		m->fwidth--;
	}
	ft_printf_int(n, m);
}
