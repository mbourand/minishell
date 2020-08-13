/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 18:38:11 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/13 20:38:04 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <string.h>
# include <errno.h>
# include <dirent.h>

# define DEBUG		1

# define BUFF_SIZE	2
# define TRUE		1
# define FALSE		0
# define SUCCESS	0
# define FAILURE	-1

# define OP_SEMICOL ";"
# define OP_PIPE "|"
# define OP_APPEND ">>"
# define OP_REDIROUT ">"
# define OP_REDIRIN "<"

typedef struct	s_token
{
	char		*text;
	int			is_operator;
}				t_token;

/*
**	Tokens : liste de t_token
**	Commands : liste de char**
*/

typedef struct	s_env
{
	char *key;
	char *val;
}				t_env;

typedef struct	s_range
{
	size_t min;
	size_t max;
}				t_range;

/*
**	save = sauvegarde du fd écrasé (valeur obenue avec dup())
**	target = le fd redirigé (donc 1 pour '>' et 0 pour '<' par exemple)
*/
typedef struct	s_redir
{
	int	save;
	int	target;
}				t_redir;


typedef struct	s_shell
{
	char	*cwd;
	char	*input;
	char	**path;
	t_list	*tokens;
	t_list	*env;
	t_list	**commands;
	t_list	*lst_redir;
}				t_shell;

int		set_cwd(char **cwd, size_t size);
void	print_prompt(t_shell *shell);
void	process_command(t_shell *shell);
void	get_tokens(t_shell *shell);
size_t	operator_length(char *str);
int		is_blank(char c);
int		is_quote(char c);
void	parse_command(t_shell *shell);
t_env	*parse_env(char *str);
size_t	ctrloperator_length(char *str);
t_list	*init_env(char **env);
void	ft_perror(char *s);
void	free_token(void *ptr);
void	perform_expansion(t_list **cmd, t_list *env);
t_env	*get_env(t_list *env, char *key);
char	*ft_strcut(char *src, size_t cut_start, size_t len);
char	*get_var_name(char *str);
t_range	*new_range(size_t min, size_t max);
void	free_shell(t_shell *shell);
int		btin_cd(t_shell *shell, t_list *command);
int		btin_env(t_list *env, t_list *command);
int		btin_export(t_list *env, t_list	*command);
void	btin_pwd(t_shell *shell, t_list *command);
int		btin_unset(t_list *env, t_list *command);
int		check_pipe(t_list *command, size_t i);
int		check_red(t_list *command, size_t i);
int		check_semicol(t_list *command, size_t i);
int		commands_valid(t_shell *shell);
t_list	*perform_redirection(t_list **command);
size_t	rediroperator_length(char *str);
void	revert_redirections(t_list *lst_redir);
int		contains_rediroperator(char *str);
int		is_redirection(char *str);
int		is_operator(char *str);
char	**parse_path(t_env *env);
char	*find_exe(char **path, char *name);

#endif
