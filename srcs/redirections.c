/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 13:55:20 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/11 13:15:36 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*first_with_target(int target, t_list *lst)
{
	t_redir	*redir;

	while (lst)
	{
		redir = (t_redir*)lst->content;
		if (redir->target == target)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int		redirect(char *filename, int to, t_list **lst_redir, int oflag)
{
	t_list	*elem;
	t_redir	*redir;
	int		fd;
	int		sv;

	sv = dup(to);
	if (close(to) < 0)
		return close(sv);
	if ((fd = open(filename, oflag, 0666)) < 0)
		return close(sv);
	if ((fd != to && (dup2(fd, to) < 0 || close(fd) < 0)))
	{
		close(fd);
		return close(sv);
	}
	if (!(elem = first_with_target(to, *lst_redir)))
	{
		ft_lstadd_back(lst_redir,
			(elem = ft_lstnew(malloc_zero(sizeof(t_redir)))));
		redir = (t_redir*)elem->content;
		redir->target = to;
		redir->save = sv;
	}
	return (0);
}

int		get_redir_flags(char *str)
{
	int offset;

	offset = 0;
	if (!rediroperator_length(str))
		offset = ft_numlen(ft_atoi(str), 10);
	if (!(ft_strcmp(str + offset, OP_REDIRIN)))
		return (O_RDONLY);
	return (O_WRONLY | O_CREAT |
		(!ft_strcmp(str + offset, OP_APPEND) ? O_APPEND : O_TRUNC));
}

void	prcs_op_redir(t_list **iter, t_list **lst_redir, t_list **command,
			size_t *i)
{
	int		to;
	int		flags;
	t_token	*content;

	content = (t_token*)(*iter)->content;
	if (rediroperator_length(content->text))
		to = !ft_strcmp(content->text, OP_REDIRIN) ? 0 : 1;
	else
		to = ft_atoi(content->text);
	flags = get_redir_flags(content->text);
	redirect(((t_token*)(*iter)->next->content)->text, to, lst_redir, flags);
	ft_lstdelat(command, *i, &free_token);
	ft_lstdelat(command, *i, &free_token);
	*iter = ft_lstat(*command, --(*i));
}

t_list	*perform_redirection(t_list **command)
{
	t_list	*lst_redir;
	t_token	*content;
	t_list	*iter;
	size_t	i;

	lst_redir = NULL;
	iter = *command;
	i = 0;
	while (iter)
	{
		content = (t_token*)iter->content;
		if (content->is_operator &&
				rediroperator_length(content->text +
				(ft_isdigit(content->text[0]) ?
				ft_numlen(ft_atoi(content->text), 10) : 0)))
			prcs_op_redir(&iter, &lst_redir, command, &i);
		iter = iter->next;
		i++;
	}
	return (lst_redir);
}
