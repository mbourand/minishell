/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:48:03 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/04 21:37:53 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	operator_length(char *str)
{
	static char	*operators[] = { OP_SEMICOL, OP_PIPE, OP_REDIRIN, OP_APPEND, OP_REDIROUT, 0 };
	size_t		len;
	size_t		i;

	i = 0;
	while (operators[i])
	{
		len = ft_strlen(operators[i]);
		if (!(ft_strncmp(str, operators[i], len)))
			return (len);
		i++;
	}
	return (0);
}

size_t	ctrloperator_length(char *str)
{
	static char	*operators[] = { OP_SEMICOL, OP_PIPE, 0 };
	size_t		len;
	size_t		i;

	i = 0;
	while (operators[i])
	{
		len = ft_strlen(operators[i]);
		if (!(ft_strncmp(str, operators[i], len)))
			return (len);
		i++;
	}
	return (0);
}

size_t	rediroperator_length(char *str)
{
	static char	*operators[] = { OP_REDIRIN, OP_APPEND, OP_REDIROUT, 0 };
	size_t		len;
	size_t		i;

	i = 0;
	while (operators[i])
	{
		len = ft_strlen(operators[i]);
		if (!(ft_strncmp(str, operators[i], len)))
			return (len);
		i++;
	}
	return (0);
}

/*
**	1 si c'est un opérateur de redirection dès le début
**	2 si le fd est explicité avant l'opérateur de redirection
*/
int		is_redirection(char *str)
{
	if (rediroperator_length(str))
		return (1);
	if (ft_isdigit(str[0]) && rediroperator_length(str + ft_numlen(ft_atoi(str), 10)))
		return (2);
	return (0);
}

int		is_operator(char *str)
{
	return (operator_length(str) || is_redirection(str));
}
