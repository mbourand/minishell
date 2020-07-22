#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <string.h>
# include <errno.h>

# define BUFF_SIZE 2

typedef struct	s_token
{
	char		*text;
}				t_token;

/** 
 * Tokens : liste de t_token
 * Commands : liste de char**
 * */

typedef struct	s_env
{
	char *key;
	char *val;
}				t_env;


typedef struct	s_shell
{
	char	*cwd;
	char	*input;
	t_list	*tokens;
	t_list	*env;
	t_list	**commands;
}				t_shell;

int		set_cwd(char **cwd, size_t size);
void	print_prompt(t_shell *shell);
void	process_command(t_shell *shell);
void	get_tokens(t_shell *shell);
size_t	operator_length(char *str);
int		is_blank(char c);
int		is_quote(char c);
void	parse_command(t_shell *shell);
size_t	ctrloperator_length(char *str);
t_list	*init_env(char **env);
void	ft_perror(char *s);
void	free_token(void *ptr);
void	perform_expansion(t_list *cmd, t_list *env);
t_env	*get_env(t_list *env, char *key);

#endif