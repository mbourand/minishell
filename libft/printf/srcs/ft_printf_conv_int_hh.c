/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_int_hh.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:13:19 by nforay            #+#    #+#             */
/*   Updated: 2020/07/31 16:54:28 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	print_width_int(t_state_machine *m)
{
	if (m->flag & (PLUS + SPACE) && m->args.hhd >= 0)
		m->fwidth--;
	if (!(m->flag & MINUS))
		while (m->fwidth && (m->fwidth - 1 > m->preci))
		{
			ft_putchar_fd(m->flag & ZERO ? '0' : ' ', m->fd);
			m->len++;
			m->fwidth--;
		}
	if (m->fwidth - m->preci > 0 && !(m->flag & MINUS))
	{
		if (m->flag & ZERO)
			ft_putchar_fd('0', m->fd);
		else
			ft_putchar_fd((m->args.hhd < 0) ? '-' : ' ', m->fd);
		m->fwidth--;
		m->len++;
	}
	if (m->flag & MINUS && m->args.hhd < 0)
	{
		ft_putchar_fd('-', m->fd);
		m->fwidth--;
		m->len++;
	}
}

static void	print_width_int_empty(t_state_machine *m)
{
	if (m->flag & (PLUS + SPACE))
	{
		m->fwidth--;
		if (m->flag & MINUS)
		{
			ft_putchar_fd((m->flag & PLUS) ? '+' : ' ', m->fd);
			m->len++;
		}
	}
	while (m->fwidth > 0)
	{
		ft_putchar_fd(' ', m->fd);
		m->len++;
		m->fwidth--;
	}
	if (!(m->flag & MINUS) && m->flag & (PLUS + SPACE) && m->args.hhd >= 0)
	{
		ft_putchar_fd((m->flag & PLUS) ? '+' : ' ', m->fd);
		m->len++;
	}
}

static void	print_hash(t_state_machine *m)
{
	if (m->flag & ZERO)
	{
		if (m->flag & (PLUS + SPACE) && m->args.hhd >= 0)
		{
			ft_putchar_fd((m->flag & PLUS) ? '+' : ' ', m->fd);
			m->len++;
		}
		print_width_int(m);
	}
	else
	{
		print_width_int(m);
		if (m->flag & (PLUS + SPACE) && m->args.hhd >= 0)
		{
			ft_putchar_fd((m->flag & PLUS) ? '+' : ' ', m->fd);
			m->len++;
		}
	}
}

static void	print_conv_int_end_hh(t_state_machine *m, int size)
{
	print_hash(m);
	ft_printf_nbr_hhd_fd(m->args.hhd, size, m);
	while (m->fwidth > 0)
	{
		ft_putchar_fd(' ', m->fd);
		m->len++;
		m->fwidth--;
	}
}

void		print_conv_int_hh(t_state_machine *m)
{
	int	size;

	m->args.hhd = (signed char)va_arg(m->params, int);
	if (!(m->args.hhd) && m->flag & POINT && (!(m->preci) || m->preci == -1))
	{
		print_width_int_empty(m);
		return ;
	}
	size = get_intlen_hh(m->args.hhd, 1);
	if (m->flag & ZERO && (m->flag & POINT || m->flag & MINUS))
		m->flag &= ~ZERO;
	m->preci = (m->preci < size ? size : m->preci);
	m->fwidth = (m->fwidth < m->preci ? m->preci : m->fwidth);
	if ((m->fwidth == m->preci) && m->args.hhd < 0)
		m->fwidth = m->preci + 1;
	if (m->args.hhd < 0 && m->flag & ZERO)
	{
		ft_putchar_fd('-', m->fd);
		m->len++;
		m->fwidth--;
	}
	print_conv_int_end_hh(m, size);
}
