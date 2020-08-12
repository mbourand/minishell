/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 00:38:41 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/12 12:59:52 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline_cmd(t_list *command, t_list *env, char **path, int *exit_status)
{
	static char	*builtins[] = { BTIN_ENV, BTIN_EXPORT, BTIN_UNSET, 0 };
	char	*exec_name;
	t_token	*content;
	size_t	i;

	i = 0;
	content = (t_token*)command->content;
	exec_name = ft_contains(content->text, "/") ? ft_strdup(content->text) : NULL;
	while (!exec_name && builtins[i])
	{
		if (!ft_strcmp(content->text, builtins[i]))
		{
			*exit_status = exec_btin(i, command, env);
			return ;
		}
		i++;
	}
	if (!(exec_name = find_exe(path, content->text)))
		exit(127);
	execve(exec_name, serialize_cmd(command), serialize_env(env));
	exit(126);
}
