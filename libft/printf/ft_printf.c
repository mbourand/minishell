/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:37:14 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:14:52 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void			reset_arg(t_arg *arg)
{
	arg->conv = 0;
	arg->mfw = 0;
	arg->precision = 0;
	arg->dot = 0;
	arg->zero = 0;
	arg->minus = 0;
	arg->c = 0;
}

static int		print_arg(t_arg arg, va_list ap)
{
	int i;

	i = 0;
	if (arg.conv == 'c')
		i = print_char(arg, (char)va_arg(ap, int));
	else if (arg.conv == 's')
		i = print_string(arg, va_arg(ap, void*));
	else if (arg.conv == 'd' || arg.conv == 'i')
		i = print_int(arg, va_arg(ap, int));
	else if (arg.conv == 'u')
		i = print_unsigned_int(arg, va_arg(ap, unsigned int));
	else if (arg.conv == 'x' || arg.conv == 'X')
		i = print_hex(arg, va_arg(ap, unsigned int));
	else if (arg.conv == 'p')
		i = print_pointer(arg, va_arg(ap, unsigned long));
	else if (arg.conv == '%')
		i = print_char(arg, '%');
	return (i);
}

static void		init(int *i, int *res)
{
	*i = 0;
	*res = 0;
}

static int		parse_arg(t_arg *arg, int *i, char const *format, va_list ap)
{
	int garg;

	if ((garg = get_arg(format + *i + 1, arg, ap)) == -1)
		return ((arg->conv == 0 ? 0 : -1));
	*i += garg;
	return (1);
}

int				ft_printf(char const *format, ...)
{
	int		i;
	va_list	ap;
	int		res;
	t_arg	arg;
	int		garg;

	init(&i, &res);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if ((garg = parse_arg(&arg, &i, format, ap)) <= 0)
				return (garg);
			if ((garg = (arg.conv ? print_arg(arg, ap) - 1 : -1)) == -2)
				return (-1);
			res += garg;
		}
		else
			ft_putchar_fd(format[i], 1);
		res++;
		i += (format[i] != 0);
	}
	va_end(ap);
	return (res);
}
