/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 00:38:41 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/16 00:13:23 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline_cmd(t_list *command, t_shell *shell, char **path, int *exit_status)
{
	static char	*builtins[] = { BTIN_ENV, BTIN_EXPORT, BTIN_UNSET, BTIN_CD,
		BTIN_ECHO, BTIN_PWD, 0 };
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
			*exit_status = exec_btin(i, command, shell);
			return ;
		}
		i++;
	}
	if (!(exec_name = find_exe(path, content->text)))
		exit(127);
	execve(exec_name, serialize_cmd(command), serialize_env(shell->env));
	exit(126);
}