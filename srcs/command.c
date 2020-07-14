#include "minishell.h"

/* Lit une commande du terminal et la met dans shell->input */
void	get_command(t_shell *shell)
{
	char	*input;

	if (!(get_next_line(0, &input)))
		exit(1);
	shell->input = input;
}

/**	https://www.gnu.org/software/bash/manual/html_node/Shell-Operation.html#Shell-Operation
  *	1. Reads its input from a file from a string supplied as an argument to the
  *	-c invocation option, or from the user’s terminal
  *
  *	2. Breaks the input into words and operators, obeying the quoting rules.
  *	These tokens are separated by metacharacters. Alias expansion is performed by this step.	
  *
  * 3. Parses the tokens into simple and compound commands
  * 
  * 4. Performs the various shell expansions, breaking the expanded tokens into lists of filenames
  * and commands and arguments.
  * 
  * 5. Performs any necessary redirections and removes the redirection operators and their operands
  * from the argument list.
  * 
  * 6. Executes the command
  * 
  * 7. Optionally waits for the command to complete and collects its exit status
**/
void	process_command(t_shell *shell)
{
	get_command(shell);
	get_tokens(shell);

	if (!ft_strncmp(((t_token*)(shell->tokens->content))->text, "testok", 7)) //for testing purposes only
	{
		int fd = open("./README.md", O_RDONLY);
		if (fd == -1)
			ft_perror("./README.md");
		else
			close(fd);
	}
	else if (!ft_strncmp(((t_token*)(shell->tokens->content))->text, "testerr", 8)) //for testing purposes only
	{
		int fd = open("./REEEEEEEEADME.md", O_RDONLY);
		if (fd == -1)
			ft_perror("./REEEEEEEEADME.md");
		else
			close(fd);
	}
}