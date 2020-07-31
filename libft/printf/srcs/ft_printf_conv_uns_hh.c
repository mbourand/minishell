/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_uns_hh.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:14:40 by nforay            #+#    #+#             */
/*   Updated: 2020/03/09 19:03:39 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_putunsnbr_fd(t_state_machine *m, unsigned char n, int fd)
{
	if (n <= 9)
	{
		ft_putchar_fd(n + 48, fd);
		m->len++;
	}
	else
	{
		ft_putunsnbr_fd(m, n / 10, fd);
		ft_putchar_fd(n % 10 + 48, fd);
		m->len++;
	}
}

static void	print_hash(t_state_machine *m, int strlen)
{
	if (m->flag & (HASH) && m->args.hhux &&
		!(m->flag & MINUS) && m->flag & POINT)
	{
		ft_printf_width_uns_hh(m, strlen);
		ft_putstr_fd((m->flag & XMAJ_CONV) ? "0X" : "0x", m->fd);
		m->len += 2;
	}
	else if (m->flag & HASH && m->args.hhux)
	{
		ft_putstr_fd((m->flag & XMAJ_CONV) ? "0X" : "0x", m->fd);
		m->len += 2;
		if (!(m->flag & MINUS))
			ft_printf_width_uns_hh(m, strlen);
	}
	else
	{
		if (!(m->flag & MINUS))
			ft_printf_width_uns_hh(m, strlen);
	}
}

static void	print_conv_uns_hh_end(t_state_machine *m, int strlen)
{
	if (!(m->args.hhux) && m->preci == 0 && m->flag & POINT)
	{
		ft_putchar_fd(' ', m->fd);
		m->len++;
	}
	else if (m->flag & X_CONV)
		ft_printf_putnbr_base_hh(m, m->args.hhux, B_HEX);
	else if (m->flag & XMAJ_CONV)
		ft_printf_putnbr_base_hh(m, m->args.hhux, B_MHEX);
	else if (m->flag & U_CONV)
		ft_putunsnbr_fd(m, m->args.hhux, m->fd);
	if (m->flag & MINUS)
		ft_printf_width_uns_hh(m, strlen);
}

void		print_conv_uns_hh(t_state_machine *m)
{
	int	strlen;

	m->preci = (m->preci < 0 ? 0 : m->preci);
	strlen = 0;
	m->args.hhux = (unsigned char)va_arg(m->params, int);
	if (!(m->args.hhux) && m->preci == 0 && m->flag & POINT && m->fwidth == 0)
		return ;
	strlen = ft_conv_base_hh(m, 0, m->args.hhux,
		(m->flag & U_CONV) ? B_TEN : B_HEX);
	print_hash(m, strlen);
	if (m->flag & POINT && strlen < m->preci)
		while ((m->preci - strlen) > 0)
		{
			ft_putchar_fd('0', m->fd);
			strlen++;
			m->len++;
		}
	print_conv_uns_hh_end(m, strlen);
}
