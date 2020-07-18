#include "minishell.h"

int init_shell(t_shell *shell, char **env)
{
	shell->cwd = NULL;
	if (!(set_cwd(&(shell->cwd), 1)))
		return (0);
	if (!(shell->env = init_env(env)))
		return (0);
	return (1);
}

int main(int ac, char **av, char **env)
{
	t_shell shell;

	(void)ac;
	(void)av;
	if (!init_shell(&shell, env))
		return (1);
	while (1)
	{
		print_prompt(&shell);
		process_command(&shell);
	}
	return (0);
}