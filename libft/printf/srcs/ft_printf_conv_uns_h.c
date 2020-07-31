/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_uns_h.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:14:33 by nforay            #+#    #+#             */
/*   Updated: 2020/03/09 19:09:32 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_putunsnbr_fd(t_state_machine *m, unsigned short int n, int fd)
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
	if (m->flag & (HASH) && m->args.hux && !(m->flag & MINUS) &&
		m->flag & POINT)
	{
		ft_printf_width_uns_h(m, strlen);
		ft_putstr_fd((m->flag & XMAJ_CONV) ? "0X" : "0x", m->fd);
		m->len += 2;
	}
	else if (m->flag & HASH && m->args.hux)
	{
		ft_putstr_fd((m->flag & XMAJ_CONV) ? "0X" : "0x", m->fd);
		m->len += 2;
		if (!(m->flag & MINUS))
			ft_printf_width_uns_h(m, strlen);
	}
	else
	{
		if (!(m->flag & MINUS))
			ft_printf_width_uns_h(m, strlen);
	}
}

static void	print_conv_uns_h_end(t_state_machine *m, int strlen)
{
	if (!(m->args.hux) && m->preci == 0 && m->flag & POINT)
	{
		ft_putchar_fd(' ', m->fd);
		m->len++;
	}
	else if (m->flag & X_CONV)
		ft_printf_putnbr_base_h(m, m->args.hux, B_HEX);
	else if (m->flag & XMAJ_CONV)
		ft_printf_putnbr_base_h(m, m->args.hux, B_MHEX);
	else if (m->flag & U_CONV)
		ft_putunsnbr_fd(m, m->args.hux, m->fd);
	if (m->flag & MINUS)
		ft_printf_width_uns_h(m, strlen);
}

void		print_conv_uns_h(t_state_machine *m)
{
	int	strlen;

	m->preci = (m->preci < 0 ? 0 : m->preci);
	strlen = 0;
	m->args.hux = (unsigned short int)va_arg(m->params, int);
	if (!(m->args.hux) && m->preci == 0 && m->flag & POINT && m->fwidth == 0)
		return ;
	strlen = ft_conv_base_h(m, 0, m->args.hux,
		(m->flag & U_CONV) ? B_TEN : B_HEX);
	print_hash(m, strlen);
	if (m->flag & POINT && strlen < m->preci)
		while ((m->preci - strlen) > 0)
		{
			ft_putchar_fd('0', m->fd);
			strlen++;
			m->len++;
		}
	print_conv_uns_h_end(m, strlen);
}
