/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:14:09 by nforay            #+#    #+#             */
/*   Updated: 2020/07/31 16:55:32 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	ft_conv_base_len(int len, unsigned long nbr)
{
	if (nbr / 16 != 0)
		len = (ft_conv_base_len(len, (nbr / 16)));
	return (++len);
}

static void	print_width(t_state_machine *m)
{
	while (m->fwidth > 0 && m->fwidth--)
	{
		ft_putchar_fd(m->flag & ZERO && !(m->flag & MINUS) ? '0' : ' ', m->fd);
		m->len++;
	}
}

static void	ft_put_pointer(t_state_machine *m, unsigned long nbr, char *base)
{
	if (m->flag & POINT && m->preci == 0)
		return ;
	if (nbr / 16 != 0)
		ft_put_pointer(m, (nbr / 16), base);
	write(1, base + (nbr % 16), 1);
}

static void	print_conv_ptr_end(t_state_machine *m, int strlen)
{
	if (m->args.p)
		ft_put_pointer(m, m->args.p, B_HEX);
	else if ((m->fwidth > 0) || (m->flag & P_CONV) == m->flag)
		ft_putchar_fd('0', m->fd);
	if (m->flag & MINUS)
	{
		m->fwidth -= strlen;
		print_width(m);
	}
}

void		print_conv_ptr(t_state_machine *m)
{
	int	strlen;

	m->args.p = (unsigned long)va_arg(m->params, unsigned long);
	if ((m->args.p) == 0)
		strlen = !(m->flag & POINT) ? 3 : 2;
	else
		strlen = 2 + ft_conv_base_len(0, m->args.p);
	if (!(m->flag & MINUS))
	{
		m->fwidth -= (m->preci >= strlen) ? m->preci : strlen;
		print_width(m);
	}
	ft_putstr_fd("0x", m->fd);
	m->len += strlen;
	if (m->flag & POINT && strlen <= m->preci)
		while ((m->preci - (strlen - 2)) > 0)
		{
			ft_putchar_fd('0', m->fd);
			strlen++;
			m->len++;
		}
	print_conv_ptr_end(m, strlen);
}
