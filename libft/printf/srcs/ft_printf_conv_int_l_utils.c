/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_int_l_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:29:19 by nforay            #+#    #+#             */
/*   Updated: 2020/07/31 16:54:34 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		get_intlen_l(long int n, int len)
{
	if (n < -9223372036854775807)
		return (19);
	if (n <= 0)
		n = -n;
	while (n >= 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	ft_printf_int_l(long int n, t_state_machine *m)
{
	if (n < -9223372036854775807)
	{
		ft_putstr_fd("922337203685477580", m->fd);
		m->fwidth -= 18;
		m->len += 18;
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
		ft_printf_int_l(n / 10, m);
		ft_putchar_fd(n % 10 + 48, m->fd);
		m->len++;
		m->fwidth--;
	}
}

void	ft_printf_nbr_l_fd(long int n, int size, t_state_machine *m)
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
	ft_printf_int_l(n, m);
}
