/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 17:51:21 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:14:52 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		print_char(t_arg arg, char c)
{
	int				i;
	int				print;

	arg.c = (arg.zero && (arg.dot == 0 || arg.precision <= 0) && arg.minus == 0)
		? '0' : ' ';
	print = print_mfw_char(arg, 0);
	i = -1;
	while (++i < ft_abs(arg.precision) - 1 && arg.precision >= 0)
	{
		ft_putchar_fd('0', 1);
		print++;
	}
	ft_putchar_fd(c, 1);
	i = -1;
	while (++i < ft_abs(arg.precision) - 1 && arg.precision < 0)
	{
		ft_putchar_fd(' ', 1);
		print++;
	}
	print += print_mfw_char(arg, 1);
	return (print + 1);
}
