/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:48:03 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/02 17:08:17 by mbourand         ###   ########.fr       */
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
