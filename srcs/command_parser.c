#include "minishell.h"

size_t	command_argc(t_list* tokens)
{
	size_t		res;
	t_token		*content;

	res = 1;
	while (tokens)
	{
		content = (t_token*)tokens->content;
		if (ctrloperator_length(content->text) > 0)
			res += 1 + (tokens->next != NULL);
		tokens = tokens->next;
	}
	return (res);
}

t_list	*fill_command(t_list *tokens, t_list **command)
{
	t_token	*content;

	if (tokens && ctrloperator_length(((t_token*)(tokens->content))->text))
	{
		ft_lstadd_back(command, ft_lstnew((t_token*)(tokens->content)));
		return (tokens->next);
	}
	while (tokens)
	{
		content = (t_token*)tokens->content;
		ft_lstadd_back(command, ft_lstnew(content));
		tokens = tokens->next;
		if (tokens && ctrloperator_length(((t_token*)(tokens->content))->text))
			break ;
	}
	return (tokens);
}

void	parse_command(t_shell *shell)
{
	t_list		*tokens;
	t_list		**commands;
	size_t		argc;
	size_t		i;

	i = 0;
	tokens = shell->tokens;
	argc = command_argc(tokens);
	if (!(commands = malloc_zero(sizeof(t_list*) * (argc + 1))))
		exit(1);
	commands[argc] = 0;
	while (i < argc)
	{
		tokens = fill_command(tokens, commands + i);
		i++;
	}
	shell->commands = commands;
}