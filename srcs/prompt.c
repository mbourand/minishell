#include "minishell.h"

void print_prompt(t_shell *shell)
{
	ft_printf("minishell:%s$", shell->cwd);
}