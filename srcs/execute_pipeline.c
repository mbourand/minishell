/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 00:38:41 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/04 15:53:11 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_execname(char *exec_name, t_list *command)
{
	char	**tmp_cmd;
	char	**tmp_env;

	execve(exec_name, tmp_cmd = serialize_cmd(command),
		tmp_env = serialize_env(g_shell.env));
	exit(126);
}

void		execute_pipeline_cmd(t_list *command, char **path, int *exit_status)
{
	static char	*builtins[] = { BTIN_ENV, BTIN_EXPORT, BTIN_UNSET, BTIN_CD,
		BTIN_ECHO, BTIN_PWD, BTIN_EXIT, 0};
	char		*ex_name;
	t_token		*content;
	size_t		i;

	i = 0;
	content = (t_token*)command->content;
	ex_name = ft_contains(content->text, "/") ? ft_strdup(content->text) : NULL;
	while (!ex_name && builtins[i])
	{
		if (!ft_strcmp(content->text, builtins[i]))
		{
			*exit_status = exec_btin(i, command);
			return ;
		}
		i++;
	}
	if (!ex_name && !(ex_name = find_exe(path, content->text)))
		exit(127);
	run_execname(ex_name, command);
}
