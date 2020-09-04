/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:32:41 by nforay            #+#    #+#             */
/*   Updated: 2020/09/04 16:22:25 by nforay           ###   ########.fr       */
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
	ft_dprintf(2, "%s%s%s\n", s, prefix, errstr);
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
