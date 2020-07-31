/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:15:00 by nforay            #+#    #+#             */
/*   Updated: 2020/07/31 16:56:33 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		intlen(int n, int len)
{
	if (n <= 0)
		n = -n;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	print_perc(t_state_machine *m)
{
	if (!(m->flag & MINUS) && m->fwidth > 1)
		while (m->fwidth > 1 && m->fwidth--)
		{
			ft_putchar_fd((m->flag & ZERO) ? '0' : ' ', m->fd);
			m->len++;
		}
	ft_putchar_fd('%', 1);
	m->fwidth--;
	m->len++;
	if (m->flag & MINUS && m->fwidth > 0)
		while (m->fwidth > 0 && m->fwidth--)
		{
			ft_putchar_fd(' ', m->fd);
			m->len++;
		}
}

void	print_conv_chr(t_state_machine *m)
{
	(void)m;
	m->args.c = va_arg(m->params, int);
	while (!(m->flag & MINUS) && m->fwidth > 1)
	{
		ft_putchar_fd(' ', m->fd);
		m->fwidth--;
		m->len++;
	}
	ft_putchar_fd(m->args.c, m->fd);
	m->fwidth--;
	m->len++;
	while (m->flag & MINUS && m->fwidth > 0)
	{
		ft_putchar_fd(' ', m->fd);
		m->fwidth--;
		m->len++;
	}
}

void	print_conv(t_state_machine *m)
{
	if (m->flag & HH)
		print_conv_hh(m);
	else if (m->flag & LL)
		print_conv_ll(m);
	else if (m->flag & H)
		print_conv_h(m);
	else if (m->flag & L)
		print_conv_l(m);
	else
		print_conv_nolength(m);
}

void	extract_aste(t_state_machine *m)
{
	if (m->flag & POINT)
		m->preci = (int)va_arg(m->params, int);
	else
	{
		m->fwidth = (int)va_arg(m->params, int);
		if (m->fwidth < 0)
		{
			m->fwidth *= -1;
			m->flag |= MINUS;
		}
	}
	if (m->preci < 0)
		m->flag = m->flag & ~POINT;
	m->flag &= ~ASTER;
}
