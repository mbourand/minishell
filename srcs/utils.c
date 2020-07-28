/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:32:41 by nforay            #+#    #+#             */
/*   Updated: 2020/07/26 15:05:52 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *s)
{
	char	*errstr;
	char	*prefix;

	errstr = strerror(errno);
	if (!s || *s == '\0')
		prefix = "";
	else
		prefix = ": ";
	ft_putstr_fd((char *)s, 2);
	ft_putstr_fd((char *)prefix, 2);
	ft_putendl_fd((char *)errstr, 2); //ft_dprintf plus clean maybe
}

t_range	*new_range(size_t min, size_t max)
{
	t_range	*range;

	if (!(range = malloc(sizeof(t_range))))
		exit(1);
	range->min = min;
	range->max = max;
	return (range);
}