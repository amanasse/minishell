/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/17 17:01:01 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "builtins.h"
# include "execution.h"
# include "../sources/libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell
{
	t_shell		*shell;
	t_lstms		*lstms;
	t_parse		*parse;
	t_env		*environ;
	char		**tab_env;	
}				t_minishell;

/*BUILTINS*/
void	builtins(char **cmd, t_minishell *minishell);

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
char	**env_in_tab(t_minishell *minishell);
int		copy_of_env(char **env, t_minishell *minishell);
int		replace_var_env(t_minishell *ms, char *str, t_export *export);
int		check_var_env(t_export *export, t_minishell *ms, char **cmd);

/*export*/
int		cmd_export(char **cmd, t_minishell *minishell);
int		check_var_env(t_export *export, t_minishell *minishell, char **cmd);

/*PARSING*/
int		ft_lexer(t_minishell *minishell, char *str);
void	ft_build_struc_parse(t_minishell *minishell, int count);
int		ft_clean_lst(t_minishell *minishell);

/*EXEC*/
int		ft_fork1(t_minishell *minishell, int *pipefd, char **cmd);
int		ft_fork2(t_minishell *minishell, int *pipefd, char **cmd);


#endif
