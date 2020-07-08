/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 17:52:03 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:16:21 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		print_s(t_arg arg, int len, char *s)
{
	int print;
	int i;

	i = -1;
	if (arg.dot == 0 || arg.precision > len)
	{
		ft_putstr_fd(s, 1);
		print = len;
	}
	else
	{
		while (arg.precision >= 0 && ++i < ft_abs(arg.precision) && s[i])
			ft_putchar_fd(s[i], 1);
		while (arg.precision < 0 && ++i < ft_abs(arg.precision))
			ft_putchar_fd(' ', 1);
		print = i;
	}
	return (print);
}

int				print_string(t_arg arg, char *s)
{
	int				print;
	int				len;
	int				dup;

	dup = !s;
	s = !s ? ft_strdup("(null)") : s;
	if (!s)
		return (-1);
	len = ft_strlen(s);
	arg.c = (arg.zero && (arg.dot == 0 || arg.precision <= 0) && arg.minus == 0)
		? '0' : ' ';
	print = print_mfw_string(arg, 0, len) + print_s(arg, len, s);
	if (dup)
		free(s);
	return (print + print_mfw_string(arg, 1, len));
}
