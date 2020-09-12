/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:14:55 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/12 16:38:11 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*malloc_zero(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		exit(1);
	ft_bzero(ptr, size);
	return (ptr);
}
