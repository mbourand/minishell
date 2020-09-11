/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 15:17:24 by nforay            #+#    #+#             */
/*   Updated: 2020/09/09 15:17:40 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		process_protected(char **res, t_token *token, t_list **prot,
				size_t *i)
{
	t_range	*range;

	range = (t_range*)((*prot)->content);
	while (*i < range->max)
		ft_straddchar(res, token->text[(*i)++], 1);
	(*i)--;
	*prot = (*prot)->next;
}