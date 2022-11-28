/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/28 10:39:45 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "builtins.h"
# include "execution.h"
# include "../sources/libft/includes/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define STDIN 0
# define STDOUT 1

# define QUOTES 0
# define STRING 1
# define PIPE 2
# define REDIR_L 3
# define REDIR_R 4
# define HEREDOC 5
# define APPEND 6
# define ENV_VAR 7
# define S_QUOTES 8

typedef struct s_minishell
{
	t_exec		exec;
	t_shell		shell;
	t_lstms		*lstms;
	t_parse		*parse;
	t_env		*environ;
	char		**tab_env;
	int			count;
	int			bool;
	int			index_cmd;
	int			fd;
	pid_t		pid;
}				t_minishell;

extern t_minishell	*g_minishell;

/*BUILTINS*/
void	builtins(t_minishell *minishell);
int		check_builtins_env(char **cmd, t_minishell *minishell);


/*pwd*/
char	*search_old_pwd(t_minishell *minishell);
int		old_pwd(t_minishell *minishell);
int		new_pwd(t_minishell *minishell, char *dir);
int		cmd_pwd(char **cmd, t_minishell *minishell);

/*cd*/
char	*go_home(t_minishell *minishell);
int		cmd_cd(char **cmd, t_minishell *minishell);

/*unset*/
int		cmd_unset(char **cmd, t_minishell *minishell);
int		var_disappear(char *str, t_minishell *minishell, t_unset *unset);
int		unset_cmd(char *str, t_minishell *minishell, t_unset *unset);

/*env*/
int		cmd_env(char **cmd, t_minishell *minishell);
void	env_in_tab(t_minishell *minishell);
int		copy_of_env(char **env, t_minishell *minishell);
int		replace_var_env(t_minishell *ms, char *str, t_export *export);
int		check_var_env(t_export *export, t_minishell *ms, char **cmd);

/*export*/
int		cmd_export(t_minishell *minishell);
int		check_var_env(t_export *export, t_minishell *minishell, char **cmd);

/*PARSING*/
int		ft_lexer(t_minishell *minishell, char *str);
int		ft_lexer_redirection(int i, char *str, t_minishell *mini);
void	ft_build_struc_parse(t_minishell *minishell, int count);
void	ft_fill_tab_cmd(t_lstms *temp, t_minishell *ms);
int		ft_clean_lst(t_minishell *minishell);
char	*ft_clean_if_quotes(char *str, t_minishell *minishell);
char	*ft_replace_dollar(char *str, char *new_str, t_minishell *minishell);
char	*ft_replace_var(char *str, t_minishell *minishell);

/*EXEC*/
char	*get_path(t_env *environ, char **cmd, t_minishell *minishell);
int		ft_fork(t_minishell *minishell, int *pipefd, int tmp_fd);
void	free_parse(t_minishell *minishell);
void	control_d_or_clear(char *str, t_minishell *minishell);
int		execution(t_minishell *minishell);
char	**make_new_tab_cmd(t_minishell *minishell);
void	exec_redirection(t_minishell *minishell, int *pipefd);
void	exec_builtin(t_minishell *minishell, int *pipefd);
void	exec_pipe(t_minishell *minishell, int *pipefd);
char	**exec_heredoc(t_minishell *minishell, char **cmd);
int		heredoc(t_minishell *minishell);
void	signals();

#endif
