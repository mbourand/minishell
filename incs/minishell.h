#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE 2

typedef struct	s_token
{
	char		*text;
	char		*expansion;
}				t_token;

/** 
 * Tokens : liste de t_token
 * Commands : liste de char**
 * */
typedef struct	s_shell
{
	char	*cwd;
	char	*input;
	t_list	*tokens;
	t_list	*commands;
}				t_shell;

int		set_cwd(char **cwd, size_t size);
void	print_prompt(t_shell *shell);
void	process_command(t_shell *shell);
void	get_tokens(t_shell *shell);


#endif