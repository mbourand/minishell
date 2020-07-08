/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 17:52:12 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:14:52 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		print_unsigned_int(t_arg arg, unsigned int nb)
{
	int				len;
	int				i;
	int				print;

	if (nb != 0 || arg.precision > 0 || !arg.dot || (arg.mfw != 0))
		len = number_len(nb, 10);
	else
		len = 0;
	i = -1;
	arg.c = (arg.zero && (arg.dot == 0 || arg.precision < 0) && arg.minus == 0)
		? '0' : ' ';
	print = print_mfw(arg, 0, len, 0);
	while (++i < ft_abs(arg.precision) - len && arg.precision >= 0)
		ft_putchar_fd('0', 1);
	print += i;
	if (arg.precision != 0 || nb != 0 || !arg.dot)
		ft_putunsignednbr_fd(nb, 1);
	else if (arg.mfw != 0)
		ft_putchar_fd(arg.c, 1);
	i = -1;
	while (++i < ft_abs(arg.precision) - len && arg.precision < 0)
		ft_putchar_fd(' ', 1);
	print += print_mfw(arg, 1, len, 0) + i;
	return (print + len);
}
