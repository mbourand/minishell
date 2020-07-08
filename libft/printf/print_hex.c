/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 17:51:31 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:14:52 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	print_value(t_arg arg, unsigned int nb)
{
	char	*hex;

	if (!(hex = ft_tobase(nb, arg.conv == 'X' ?
					"0123456789ABCDEF" : "0123456789abcdef")))
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
	while (++i < ft_abs(arg.precision) - len && arg.precision >= 0)
		ft_putchar_fd('0', 1);
	return (i);
}

int			print_hex(t_arg arg, unsigned int nb)
{
	int				len;
	int				i;
	int				print;

	if (nb != 0 || arg.precision > 0 || !arg.dot || (arg.mfw != 0))
		len = number_len(nb, 16);
	else
		len = 0;
	arg.c = (arg.zero == 1 && (arg.dot == 0 || arg.precision < 0) &&
			arg.minus == 0) ? '0' : ' ';
	print = print_mfw(arg, 0, len, 0);
	print += print_precision(arg, len);
	if (arg.precision != 0 || arg.dot == 0 || nb != 0)
	{
		if (print_value(arg, nb) == -1)
			return (-1);
	}
	else if (arg.mfw != 0)
		ft_putchar_fd(arg.c, 1);
	i = -1;
	while (++i < ft_abs(arg.precision) - len && arg.precision < 0)
		ft_putchar_fd(' ', 1);
	print += print_mfw(arg, 1, len, 0) + i;
	return (print + len);
}
