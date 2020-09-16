/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 18:38:11 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/16 14:00:18 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <linux/limits.h>
# include "libft.h"
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>

# define DEBUG		0

# define BUFF_SIZE	2
# define TRUE		1
# define FALSE		0
# define SUCCESS	0
# define FAILURE	1

# define OP_SEMICOL ";"
# define OP_PIPE "|"
# define OP_APPEND ">>"
# define OP_REDIROUT ">"
# define OP_REDIRIN "<"

# define BTIN_ENV "env"
# define BTIN_UNSET "unset"
# define BTIN_EXIT "exit"
# define BTIN_EXPORT "export"
# define BTIN_CD "cd"
# define BTIN_ECHO "echo"
# define BTIN_PWD "pwd"

# define MINISHELL_ERR1 "%s: command not found\n"
# define MINISHELL_ERR2 "minishell: %s: No such file or directory\n"
# define MINISHELL_ERR3 "minishell: exit: %s: numeric argument required\n"

# define PIPE_BEFORE 1
# define PIPE_AFTER 2

typedef struct	s_token
{
	char		*text;
	int			is_operator;
}				t_token;

typedef struct	s_env
{
	char		*key;
	char		*val;
	int			is_empty;
}				t_env;

typedef struct	s_range
{
	size_t		min;
	size_t		max;
}				t_range;

typedef struct	s_redir
{
	int			save;
	int			target;
}				t_redir;

typedef struct	s_shell
{
	char		*cwd;
	char		*input;
	char		**path;
	t_list		*tokens;
	t_list		*env;
	t_list		**commands;
	t_list		*lst_redir;
	int			**pipeline;
	int			is_parent;
	int			interrupted;
	int			exit_code;
}				t_shell;

int				set_cwd(char **cwd);
void			print_prompt();
void			process_command();
void			get_tokens();
size_t			operator_length(char *str);
int				is_blank(char c);
int				is_quote(char c);
void			parse_command();
t_env			*parse_env(char *str);
size_t			ctrloperator_length(char *str);
t_list			*init_env(char **env);
void			set_shell_level(void);
void			ft_perror(char *s);
void			free_token(void *ptr);
void			perform_expansion(t_list **cmd, t_list *env);
t_env			*get_env(t_list *env, char *key);
char			*ft_strcut(char *src, size_t cut_start, size_t len);
char			*get_var_name(char *str);
t_range			*new_range(size_t min, size_t max);
void			free_shell();
int				btin_cd(t_list *command);
int				btin_echo(t_list *command);
int				btin_env(t_list *command);
int				btin_exit(t_list *command);
int				btin_export(t_list	*command);
int				btin_pwd(t_list *command);
int				btin_unset(t_list *command);
void			free_env(t_env *env);
int				only_quotes(char *s);
int				check_pipe(t_list *command, size_t i);
int				check_red(t_list *command, size_t i);
int				check_semicol(t_list *command, size_t i);
int				commands_valid();
t_list			*perform_redirection(t_list **command);
size_t			rediroperator_length(char *str);
void			revert_redirections(t_list *lst_redir);
int				contains_rediroperator(char *str);
int				is_redirection(char *str);
int				is_operator(char *str);
char			**parse_path(t_env *env);
char			*find_exe(char **path, char *name);
int				exec_command(t_list *command, char **path, t_list *env);
void			execute_pipeline_cmd(t_list *command, char **path);
void			process_pipeline(size_t *i);
int				is_pipe(t_list *command);
char			**serialize_cmd(t_list *cmd);
char			**serialize_env(t_list *env);
int				exec_btin(size_t i, t_list *cmd);
void			redirect_fd(int fd, int to);
int				get_near_pipes(t_list **command, size_t i);
void			pipe_redirection(int pipes, int pipe_index);
void			sighandler(void);
void			free_nothing(void *ptr);
int				get_redir_flags(char *str);
int				check_redirections(t_list *command);
void			fill_pipeline(size_t i);
void			new_word(t_list **iter, t_token **token);
void			prcs_character(t_token *token, size_t *i);
void			prcs_operator(t_token **token, size_t *i, t_list **iter);
void			prcs_space(t_token **token, size_t *i, t_list **iter);
void			prcs_quote(t_token *token, size_t *i);
void			prcs_redirection(t_token **token, size_t *i, t_list **iter);
void			process_protected(char **res, t_token *token, t_list **prot,
					size_t *i);

extern			t_shell g_shell;

#endif
