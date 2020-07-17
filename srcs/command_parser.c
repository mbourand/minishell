#include "minishell.h"

size_t	command_argc(t_list* tokens)
{
	size_t		res;
	t_token		*content;

	res = 1;
	while (tokens)
	{
		content = (t_token*)tokens->content;
		if (ctrloperator_length(content->text) > 0 && tokens->next)
			res++;
		tokens = tokens->next;
	}
	return (res);
}

size_t	command_len(t_list* tokens)
{
	t_token	*content;
	size_t	len;

	len = 0;
	while (tokens)
	{
		content = ((t_token*)tokens->content);
		if (ctrloperator_length(content->text) > 0)
			break ;
		len += ft_strlen(content->text);
		tokens = tokens->next;
	}
	return (len);
}

t_list	*fill_command(t_list *tokens, char **command)
{
	t_token	*content;

	while (tokens)
	{
		content = (t_token*)tokens->content;
		*command = ft_strjoin(*command, content->text);
		*command = ft_straddchar(*command, ' ', 1);
		tokens = tokens->next;
		if (ctrloperator_length(content->text) > 0)
			break ;
	}
	return (tokens);
}

void	parse_command(t_shell *shell)
{
	t_list		*tokens;
	char		**commands;
	size_t		argc;
	size_t		i;

	i = 0;
	tokens = shell->tokens;
	argc = command_argc(tokens);
	if (!(commands = malloc(sizeof(char*) * (argc + 1))))
		exit(1);
	commands[argc] = 0;
	while (commands[i])
	{
		if (!(commands[i] = malloc(sizeof(char) * (command_len(tokens) + 1))))
			exit(1);
		tokens = fill_command(tokens, commands + i);
		i++;
	}
	shell->commands = commands;

	for (int j = 0; commands[j]; j++)
		ft_printf("%s\n", commands[j]);
}