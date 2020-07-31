/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_int_hh_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:17:47 by nforay            #+#    #+#             */
/*   Updated: 2020/07/31 16:54:01 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_printf_nbr_hhd_fd(signed char n, int size, t_state_machine *m)
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
	ft_printf_signed_char(n, m);
}

int		get_intlen_hh(signed char n, int len)
{
	if (n == -128)
		return (3);
	if (n <= 0)
		n = -n;
	while (n >= 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	ft_printf_signed_char(signed char n, t_state_machine *m)
{
	if (n == -128)
	{
		ft_putstr_fd("12", m->fd);
		m->fwidth -= 2;
		m->len += 2;
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
		ft_printf_signed_char(n / 10, m);
		ft_putchar_fd(n % 10 + 48, m->fd);
		m->len++;
		m->fwidth--;
	}
}
