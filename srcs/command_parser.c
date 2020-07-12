#include "minishell.h"

size_t	command_argc(t_list* tokens)
{
	static char	*operators[] = { ";", "|", 0 };
	size_t		i;
	t_token		*content;

	i = 0;
	while (tokens)
	{
		content = (t_token*)tokens->content;
		while (operators[i])
		{
			
			i++;
		}
		tokens = tokens->next;
	}
}

void	parse_command(t_shell *shell)
{
	t_list*		tokens;
	t_token		content;
	char		**command;
	size_t		argc;

	tokens = shell->tokens;
	while (tokens)
	{
		content = (t_token*)tokens->content;
		argc = command_argc(tokens);
		if (!(command = malloc(sizeof(char*) * argc)))
			exit(1);
		tokens = fill_command(tokens, command, argc);
		shell->commands = ft_lstadd_back(&(shell->commands), ft_lstnew(command));
	}
}