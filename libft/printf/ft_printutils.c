/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:58:16 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:14:52 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		print_mfw(t_arg arg, int expected_minus, long len, int negative)
{
	int i;

	i = -1;
	if (arg.precision < 0)
		return (0);
	if (arg.minus == expected_minus && arg.mfw > arg.precision)
	{
		while (++i < arg.mfw -
				(arg.precision < len ? len : (arg.precision + negative)))
			ft_putchar_fd(arg.c, 1);
		return (i);
	}
	return (0);
}

int		print_mfw_pointer(t_arg arg, int expected_minus, long len, int negative)
{
	int i;

	i = -1;
	if (arg.precision - 2 < 0)
		return (0);
	if (arg.minus == expected_minus && arg.mfw > arg.precision)
	{
		while (++i < arg.mfw -
				(arg.precision < len ? len : (arg.precision + negative)))
			ft_putchar_fd(arg.c, 1);
		return (i);
	}
	return (0);
}

int		print_mfw_string(t_arg arg, int expected_minus, long len)
{
	int i;

	i = -1;
	if (arg.precision < 0)
		return (0);
	if (arg.minus == expected_minus && arg.mfw > (arg.dot && arg.precision < len
				&& arg.precision >= 0 ? arg.precision : len))
	{
		while (++i < arg.mfw -
				(arg.dot && arg.precision < len &&
				arg.precision >= 0 ? arg.precision : len))
			ft_putchar_fd(arg.c, 1);
		return (i);
	}
	return (0);
}

int		skip_charset(const char *s, const char *charset)
{
	int i;

	i = 0;
	while (s[i] && ft_strchr(charset, s[i]))
		i++;
	return (i);
}

int		print_mfw_char(t_arg arg, int expected_minus)
{
	int i;

	i = -1;
	if (arg.precision < 0)
		return (0);
	if (arg.minus == expected_minus && arg.mfw > arg.precision)
	{
		while (++i < arg.mfw - (arg.precision < 1 ? 1 : arg.precision))
			ft_putchar_fd(arg.c, 1);
		return (i);
	}
	return (0);
}
