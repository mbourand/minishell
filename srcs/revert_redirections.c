/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revert_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 01:18:27 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/03 01:45:08 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	revert_redirections(t_list *lst_redir)
{
	t_redir	*redir;

	while (lst_redir)
	{
		redir = (t_redir*)lst_redir->content;
		if (close(redir->target) < 0)
			exit(1);
		if (dup2(redir->save, redir->target) < 0)
			exit(1);
		if (close(redir->save) < 0)
			exit(1);
		lst_redir = lst_redir->next;
	}
}
