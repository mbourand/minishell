/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 17:51:47 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:15:44 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	print_zerox(t_arg arg, int len, int *print)
{
	int i;

	i = -1;
	if (arg.c == '0')
		ft_putstr_fd("0x", 1);
	*print = print_mfw_pointer(arg, 0, len + 2, 0) + 2;
	if (arg.c == ' ')
		ft_putstr_fd("0x", 1);
	while (++i < ft_abs(arg.precision) - 2 - len && arg.precision >= 0)
		ft_putchar_fd('0', 1);
	(*print) += i;
}

static int	print_value(unsigned long nb)
{
	char *hex;

	if (!(hex = ft_tobase(nb, "0123456789abcdef")))
		return (-1);
	ft_putstr_fd(hex, 1);
	if (hex)
		free(hex);
	return (1);
}

static int	print_precision(t_arg arg, int len)
{
	int i;

	i = -1;
	while (++i < ft_abs(arg.precision) - len && arg.precision < 0)
		ft_putchar_fd(' ', 1);
	return (i);
}

int			print_pointer(t_arg arg, unsigned long nb)
{
	int				len;
	int				print;

	print = 0;
	if (!(arg.precision > 0 || arg.dot == 0 || nb != 0) && !(arg.mfw != 0
				&& arg.precision > 0))
		len = 0;
	else
		len = number_lenl(nb, 16);
	arg.c = (arg.zero && (arg.dot == 0 || arg.precision < 0) &&
			arg.minus == 0) ? '0' : ' ';
	arg.precision += 2;
	print_zerox(arg, len, &print);
	if (arg.precision - 2 > 0 || arg.dot == 0 || nb != 0)
	{
		if (print_value(nb) == -1)
			return (-1);
	}
	else if (arg.mfw != 0 && arg.precision - 2 > 0)
		ft_putchar_fd(arg.c, 1);
	print += print_mfw_pointer(arg, 1, len + 2, 0) + print_precision(arg, len);
	return (print + len);
}
