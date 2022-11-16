/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:33 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/16 11:40:32 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/parsing.h"
# include "../includes/builtins.h"
# include "../includes/execution.h"
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
}				t_minishell;

/*BUILTINS*/
void	builtins(char **cmd, t_minishell *minishell);

/*pwd*/
char	*search_old_pwd(t_minishell *minishell);
int		old_pwd(t_minishell *minishell);
int		new_pwd(t_minishell *minishell, char *dir);
int		cmd_pwd(char **cmd, t_minishell *minishell);

/*cd*/
int		cmd_cd(char **cmd, t_minishell *minishell);

/*env*/
int		cmd_env(char **cmd, t_minishell *minishell);
char	**env_in_tab(t_minishell *minishell);
int		copy_of_env(char **env, t_minishell *minishell);

/*export*/
int		cmd_export(char **cmd, t_minishell *minishell);
int		check_var_env(t_export *export, t_minishell *minishell, char **cmd);

/*PARSING*/
int		ft_lexer(t_minishell *minishell, char *str);
void	ft_build_struc_parse(t_minishell *minishell, int count);
int		ft_clean_lst(t_minishell *minishell);

/*EXEC*/
int		ft_fork1(t_minishell *minishell, int *pipefd);
int		ft_fork2(t_minishell *minishell, int *pipefd);


#endif
