/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_n.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:14:05 by nforay            #+#    #+#             */
/*   Updated: 2020/03/09 17:38:55 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	print_conv_n(t_state_machine *m)
{
	if (m->flag & HH)
	{
		m->args.hhn = (signed char*)va_arg(m->params, signed char*);
		*m->args.hhn = (signed char)m->len;
	}
	else if (m->flag & LL)
	{
		m->args.lln = (long long int*)va_arg(m->params, long long int*);
		*m->args.lln = (long long int)m->len;
	}
	else if (m->flag & H)
	{
		m->args.hn = (short int*)va_arg(m->params, short int*);
		*m->args.hn = (short int)m->len;
	}
	else if (m->flag & L)
	{
		m->args.ln = (long int*)va_arg(m->params, long int*);
		*m->args.ln = (long int)m->len;
	}
	else
	{
		m->args.n = (int*)va_arg(m->params, int*);
		*m->args.n = (int)m->len;
	}
}
