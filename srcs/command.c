/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:47:42 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/09 15:54:43 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		simple_command(int i)
{
	char	*text;

	perform_expansion(g_shell.commands + i, g_shell.env);
	if (!check_redirections(g_shell.commands[i]))
	{
		ft_perror("minishell");
		g_shell.exit_code = 1;
		return (0);
	}
	text = ((t_token*)g_shell.commands[i]->content)->text;
	g_shell.lst_redir = perform_redirection(g_shell.commands + i);
	g_shell.path = parse_path(get_env(g_shell.env, "PATH"));
	if (g_shell.commands[i] && *text)
	{
		g_shell.exit_code = exec_command(g_shell.commands[i], g_shell.path,
			g_shell.env);
		if (g_shell.exit_code == 127)
			ft_dprintf(STDERR_FILENO, (g_shell.path) ? MINISHELL_ERR1 : MINISHELL_ERR2, text);
	}
	revert_redirections(g_shell.lst_redir);
	ft_lstclear(&(g_shell.lst_redir), &free);
	ft_free_tab(&(g_shell.path));
	return (1);
}

void	get_command(void)
{
	char	*input;
	int		ret;

	ret = get_next_line(STDIN_FILENO, &input);
	if (ret == 0)
	{
		ft_dprintf(STDERR_FILENO, "exit\n");
		exit(g_shell.exit_code);
	}
	if (ret < 0)
		exit(1);
	g_shell.input = input;
}

void	process_command(void)
{
	size_t i;

	i = 0;
	get_command();
	get_tokens();
	parse_command();
	if (!commands_valid())
	{
		ft_putendl_fd("minishell: Invalid syntax.", 2);
		g_shell.exit_code = 2;
		free_shell();
		return ;
	}
	while (g_shell.commands[i] && !g_shell.interrupted)
	{
		if (is_pipe(g_shell.commands[i + 1]))
			process_pipeline(&i);
		else if (((t_token*)(g_shell.commands[i]->content))->is_operator && !is_redirection(((t_token*)(g_shell.commands[i]->content))->text))
			i++;
		else
			simple_command(i++);
	}
	g_shell.interrupted = 0;
	free_shell();
}
