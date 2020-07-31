/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:12:29 by nforay            #+#    #+#             */
/*   Updated: 2020/07/31 17:01:04 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		error(const char *input, t_state_machine *machine)
{
	(void)input;
	machine->state = LETTER;
	machine->flag = 0;
	machine->preci = -1;
	machine->fwidth = 0;
	ft_putchar_fd(input[0], machine->fd);
	machine->len++;
	return (1);
}

static int		conv(const char *input, t_state_machine *machine)
{
	static char	*str_conv = ALLCONV;
	int			i;

	i = 0;
	while (i < NB_CONV)
	{
		if (ft_strncmp(input, str_conv + i, 1) == FALSE)
		{
			machine->flag |= (1 << i) << 12;
			print_conv(machine);
			machine->state = LETTER;
			machine->flag = 0;
			machine->preci = -1;
			machine->fwidth = 0;
			return (1);
		}
		i++;
	}
	machine->state = ERROR;
	return (0);
}

static int		flag(const char *input, t_state_machine *machine)
{
	static char	*str_flag[NB_FLAG] = {F_HH, F_LL, F_MINUS, F_ZERO,
		F_ASTER, F_HASH, F_SPACE, F_PLUS, F_H, F_L, F_POINT};
	int			i;

	i = -1;
	while (++i < NB_FLAG)
	{
		if (!(machine->flag & POINT) && (input[0] > '0' && input[0] <= '9')
				&& (machine->fwidth = ft_atoi(input)))
			return (intlen(machine->fwidth, 0));
		if ((machine->flag & POINT) && (ft_isdigit(input[0])))
		{
			machine->preci = ft_atoi(input);
			return (!(machine->preci) ? 1 : intlen(machine->preci, 0));
		}
		if (ft_strncmp(input, str_flag[i], (i < 2 ? 2 : 1)) == FALSE)
		{
			machine->flag |= (1 << i);
			if (machine->flag & ASTER)
				extract_aste(machine);
			return (i < 2 ? 2 : 1);
		}
	}
	machine->state = CONV;
	return (0);
}

static int		letter(const char *input, t_state_machine *machine)
{
	if (*input == '%')
		machine->state = FLAG;
	else
	{
		ft_putchar_fd(*input, machine->fd);
		machine->len++;
	}
	return (1);
}

int				ft_printf(const char *format, ...)
{
	static t_function	process[4] = {letter, flag, conv, error};
	t_state_machine		machine;
	int					ret;

	ft_bzero(&machine, sizeof(machine));
	machine.preci = -1;
	va_start(machine.params, format);
	machine.fd = 1;
	machine.state = LETTER;
	while (format != NULL && *format != '\0')
	{
		if ((ret = process[machine.state](format, &machine)) >= 0)
			format += ret;
	}
	va_end(machine.params);
	return (machine.len);
}
