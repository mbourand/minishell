/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 11:53:47 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:14:52 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	get_flags(char const *format, t_arg *arg, int *i)
{
	while (format[*i] == '0' || format[*i] == '-')
	{
		arg->minus = (format[*i] != '0' || arg->minus == 1);
		arg->zero = (format[(*i)++] == '0' || arg->zero == 1);
	}
}

static int	get_mfw(char const *format, t_arg *arg, int *i, va_list ap)
{
	if (format[*i] == '*')
	{
		arg->mfw = va_arg(ap, int);
		if (arg->mfw > 2147483646 || arg->mfw < -2147483646)
			return (-1);
		arg->minus = (arg->mfw < 0 || arg->minus);
		arg->mfw = arg->mfw < 0 ? arg->mfw * -1 : arg->mfw;
		(*i)++;
	}
	else
	{
		arg->mfw = ft_atoi(format + *i);
		if (arg->mfw > 2147483646 || arg->mfw < -2147483646)
			return (-1);
		(*i) += skip_charset(format + *i, "0123456789");
	}
	return (0);
}

static int	get_precision(char const *format, t_arg *arg, int *i, va_list ap)
{
	if (format[*i] == '.')
	{
		arg->dot = 1;
		if (format[*i + 1] == '*')
		{
			arg->precision = va_arg(ap, int);
			if (arg->precision < 0)
			{
				arg->precision = 0;
				arg->dot = 0;
			}
			(*i) += 2;
		}
		else
		{
			arg->precision = ft_atoi(format + *i + 1);
			if (arg->precision < 0)
				(*i)++;
			(*i) += skip_charset(format + *i + 1, "0123456789") + 1;
		}
	}
	if (arg->precision < -2147483646 || arg->precision > 2147483646)
		return (-1);
	return (0);
}

int			get_arg(char const *format, t_arg *arg, va_list ap)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	reset_arg(arg);
	get_flags(format, arg, &i);
	if (get_mfw(format, arg, &i, ap) == -1 ||
		get_precision(format, arg, &i, ap) == -1)
		ret = -1;
	if (ft_strchr("cspdiuxX%", format[i]))
		arg->conv = format[i];
	return (ret == -1 ? ret : i + 1);
}
