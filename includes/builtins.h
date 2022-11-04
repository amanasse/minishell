/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:21:36 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/04 12:35:08 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <sys/types.h>
# include <dirent.h>
# include "../includes/minishell.h"


typedef struct s_env
{
	struct s_env	*next;
	char			*str;
}					t_env;

typedef struct s_shell
{
	t_env	        *environ;
	char			**cmd;
    char            *pwd;
    char            *old_pwd;
}					t_shell;



/*BUILTINS*/

void	builtins(char **cmd, t_env *c_env);
int	*cmd_cd(char **cmd, t_env *c_env);
int		cmd_exit(char **cmd);
void	cmd_pwd(char **cmd, t_env *c_env);
void    cmd_echo(char **cmd);

/*UTILS*/
int		ft_strcmp(char *s1, char *s2);
int     ft_str_is_numeric(char *str);
int     ft_atoi_check(const char *nptr);
int     ft_atoi(const char *nptr);


/*GESTION DE LENV*/

void    ft_view_env(t_env *lst);
void	ft_lstclear_env(t_env *lst);
int		get_home(t_shell *shell);
void	copy_of_env(char **env, t_shell *shell);

t_env	*ft_lstnew_env(void *content);
void	ft_lstadd_back_env(t_env **lst, t_env *new);



#endif