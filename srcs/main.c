#include "minishell.h"

int init_shell(t_shell *shell)
{
	shell->cwd = NULL;
	if (!(set_cwd(&(shell->cwd), 1)))
		return (0);
	return (1);
}

int main(void)
{
	t_shell shell;

	if (!init_shell(&shell))
		return (1);
	while (1)
	{
		print_prompt(&shell);
		process_command(&shell);
	}
	return (0);
}