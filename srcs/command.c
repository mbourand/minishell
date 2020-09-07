/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:47:42 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/06 03:03:14 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Lit une commande du terminal et la met dans shell->input
*/
void	get_command(void)
{
	char	*input;
	int		ret;

	ret = get_next_line(STDIN_FILENO, &input);
	if (ret == 0)
	{
		ft_dprintf(STDERR_FILENO, "exit\n");
		exit(0);
	}
	if (ret < 0)
		exit(1);
	g_shell.input = input;
}

/*	https://www.gnu.org/software/bash/manual/html_node/Shell-Operation.html#Shell-Operation
**	1. Reads its input from a file from a string supplied as an argument to the
**	-c invocation option, or from the user’s terminal
**
**	2. Breaks the input into words and operators, obeying the quoting rules.
**	These tokens are separated by metacharacters. Alias expansion is performed by this step.
**
**	3. Parses the tokens into simple and compound commands
**
**	4. Performs the various shell expansions, breaking the expanded tokens into lists of filenames
**	and commands and arguments.
**
**	5. Performs any necessary redirections and removes the redirection operators and their operands
**	from the argument list.
**
**	6. Executes the command
**
**	7. Optionally waits for the command to complete and collects its exit status
*/

/*
**	Vérifier si c'est le début d'une pipeline, auquel cas exécuter
**	une autre fonction qui fait les redirections et tout le bordel dans les fork directement
**	Et faire les redirectgions des pipes avant les redirections des commandes !!!
*/
void	process_command()
{
	size_t i;

	i = 0;
	get_command();
	get_tokens();
	parse_command();
	if (!commands_valid())
	{
		ft_putendl_fd("Commande invalide", 2);
		free_shell();
		return ;
	}
	while (g_shell.commands[i] && !g_shell.interrupted)
	{
		if (is_pipe(g_shell.commands[i + 1]))
		{
			process_pipeline(&i);
			continue ;
		}
		if (((t_token*)(g_shell.commands[i]->content))->is_operator)
		{
			i++;
			continue ;
		}
		perform_expansion(g_shell.commands + i, g_shell.env);
		g_shell.lst_redir = perform_redirection(g_shell.commands + i);
		g_shell.path = parse_path(get_env(g_shell.env, "PATH"));
		if (g_shell.commands[i])
			g_shell.exit_code = exec_command(g_shell.commands[i], g_shell.path, g_shell.env);
		//ft_printf("exit code: %d\n", shell->exit_code);
		revert_redirections(g_shell.lst_redir);
		ft_lstclear(&(g_shell.lst_redir), &free);
		ft_free_tab(&(g_shell.path));
		i++;
	}
	g_shell.interrupted = 0;
	free_shell();
}
