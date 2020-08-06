/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 21:27:09 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/06 03:29:39 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**serialize_cmd(t_list *cmd)
{
	char	**res;
	size_t	i;

	i = 0;
	if (!(res = malloc_zero(sizeof(char*) * (ft_lstsize(cmd) + 1))))
		exit(1);
	while (cmd)
	{
		res[i] = ft_strdup(((t_token*)(cmd->content))->text);
		cmd = cmd->next;
		i++;
	}
	return (res);
}

char	**serialize_env(t_list *env)
{
	char	**res;
	size_t	i;

	i = 0;
	if (!(res = malloc_zero(sizeof(char*) * (ft_lstsize(env) + 1))))
		exit(1);
	while (env)
	{
		res[i] = ft_strjoin(((t_env*)env->content)->key, "=");
		res[i] = ft_strjoin(res[i], ((t_env*)env->content)->val);
		env = env->next;
		i++;
	}
	return (res);
}

void	run_exec(char *name, t_list *cmd, t_list *env)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		exit(1);
	if (!pid)
	{
		if (execve(name, serialize_cmd(cmd), serialize_env(env)) == -1)
			exit(1);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

void	exec_btin(size_t i, t_list *cmd, t_list *env)
{
	static int (*btins[])(t_list*, t_list*) = { &btin_env, &btin_export,
		&btin_unset, 0};
	(btins[i])(env, cmd);
}

/*
**	https://www.gnu.org/software/bash/manual/html_node/Command-Search-and-Execution.html#Command-Search-and-Execution
*/
void	exec_command(t_list *command, char **path, t_list *env)
{
	static char	*builtins[] = { BTIN_ENV, BTIN_EXPORT, BTIN_UNSET, 0 };
	size_t		i;
	t_token		*content;
	char		*exec_name;

	if (!command)
		return ;
	content = (t_token*)command->content;
	i = 0;
	exec_name = ft_contains(content->text, "/") ? content->text : NULL;
	while (!exec_name && builtins[i])
	{
		if (!ft_strcmp(content->text, builtins[i]))
		{
			exec_btin(i, command, env);
			return ;
		}
		i++;
	}
	if (!exec_name)
		exec_name = find_exe(path, content->text);
	if (exec_name)
		run_exec(exec_name, command, env);
}
