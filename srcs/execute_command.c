/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 21:27:09 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/09 13:01:28 by nforay           ###   ########.fr       */
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
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(res = malloc_zero(sizeof(char*) * (ft_lstsize(env) + 1))))
		exit(1);
	while (env)
	{
		res[i] = ft_strjoin(((t_env*)env->content)->key, "=");
		tmp = res[i];
		res[i] = ft_strjoin(res[i], ((t_env*)env->content)->val);
		ft_free(&tmp);
		env = env->next;
		i++;
	}
	return (res);
}

int		run_exec(char *name, char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	if ((pid = fork()) == -1)
		exit(1);
	if (pid == 0)
	{
		if (!name)
			exit(127);
		execve(name, cmd, env);
		exit(126);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			exit(1);
	}
	ft_free_tab(&cmd);
	ft_free_tab(&env);
	return (status);
}

int		exec_btin(size_t i, t_list *cmd)
{
	static int (*btins[])(t_list*) = { &btin_env, &btin_export,
		&btin_unset, &btin_cd, &btin_echo, &btin_pwd, &btin_exit, 0};

	return ((btins[i])(cmd));
}

int		exec_command(t_list *command, char **path, t_list *env)
{
	static char	*builtins[] = { BTIN_ENV, BTIN_EXPORT, BTIN_UNSET, BTIN_CD,
		BTIN_ECHO, BTIN_PWD, BTIN_EXIT, 0};
	size_t		i;
	t_token		*content;
	char		*ex_name;
	int			exit_code;

	content = (t_token*)command->content;
	i = 0;
	ex_name = ft_contains(content->text, "/") ? ft_strdup(content->text) : NULL;
	while (!ex_name && builtins[i])
	{
		if (!ft_strcmp(content->text, builtins[i]))
			return (exec_btin(i, command));
		i++;
	}
	if (!ex_name && path)
		ex_name = find_exe(path, content->text);
	exit_code = run_exec(ex_name, serialize_cmd(command), serialize_env(env));
	if (WIFEXITED(exit_code))
		exit_code = WEXITSTATUS(exit_code);
	else if (WIFSIGNALED(exit_code))
		exit_code += 128;
	ft_free(&ex_name);
	return (exit_code);
}
