/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:47:42 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/11 04:47:01 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Lit une commande du terminal et la met dans shell->input
*/
void	get_command(t_shell *shell)
{
	char	*input;

	if (!(get_next_line(0, &input)))
		exit(1);
	shell->input = input;
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
*	Vérifier si c'est le début d'une pipeline, auquel cas exécuter
*	une autre fonction qui fait les redirections et tout le bordel dans les fork directement
*	Et faire les redirectgions des pipes avant les redirections des commandes !!!
*/
void	process_command(t_shell *shell)
{
	size_t i;

	i = 0;
	get_command(shell);
	get_tokens(shell);
	parse_command(shell);
	if (!commands_valid(shell))
	{
		ft_putendl_fd("Commande invalide", 2);
		free_shell(shell);
		return ;
	}
	while (shell->commands[i])
	{
		if (is_pipe(shell->commands[i + 1]))
		{
			process_pipeline(shell, &i);
			continue ;
		}
		if (((t_token*)(shell->commands[i]->content))->is_operator)
		{
			i++;
			continue ;
		}
		perform_expansion(shell->commands + i, shell->env);
		shell->lst_redir = perform_redirection(shell->commands + i);
		shell->path = parse_path(get_env(shell->env, "PATH"));
		if (shell->commands[i])
			shell->exit_code = exec_command(shell->commands[i], shell->path, shell->env);
		//ft_printf("exit code: %d\n", shell->exit_code);
		revert_redirections(shell->lst_redir);
		ft_lstclear(&(shell->lst_redir), &free);
		ft_free_tab(&(shell->path));
		i++;
	}
	free_shell(shell);
}
