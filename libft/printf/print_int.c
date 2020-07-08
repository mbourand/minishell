/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 17:51:39 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:14:52 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	print_nb(t_arg arg, int nb, int len)
{
	int i;
	int print;

	i = -1;
	while (++i < ft_abs(arg.precision) - len + (nb < 0) && arg.precision >= 0)
		ft_putchar_fd('0', 1);
	print = i;
	if (nb != 0 || arg.precision > 0 || !arg.dot)
		ft_putnbr_fd(nb, 1);
	else if (arg.mfw != 0)
		ft_putchar_fd(arg.c, 1);
	i = -1;
	while (++i < ft_abs(arg.precision) - len + (nb < 0) && arg.precision < 0)
		ft_putchar_fd(' ', 1);
	return (print + i);
}

int			print_int(t_arg arg, int nb)
{
	int				len;
	int				print;

	if (nb != 0 || arg.precision > 0 || !arg.dot || (arg.mfw != 0))
		len = number_len(nb, 10);
	else
		len = 0;
	arg.c = (arg.zero && (arg.dot == 0 || arg.precision < 0) && arg.minus == 0)
		? '0' : ' ';
	if (nb < 0 && arg.zero && (!arg.dot || arg.precision < 0))
		ft_putchar_fd('-', 1);
	print = print_mfw(arg, 0, len, (nb < 0));
	if (nb < 0 && (!arg.zero || (arg.zero && (arg.dot && arg.precision >= 0))))
		ft_putchar_fd('-', 1);
	print += print_nb(arg, nb, len);
	print += print_mfw(arg, 1, len, (nb < 0));
	return (print + len);
}
