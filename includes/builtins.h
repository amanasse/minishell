/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:21:36 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/15 15:03:56 by amanasse         ###   ########.fr       */
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
	int				printable;
}					t_env;

typedef struct s_shell
{
	t_env	        *environ;
	char			**tab_env;
	char			**cmd;
	int				i;
	int				j;
    char            *pwd;
    char            *old_pwd;
	int				status;
}					t_shell;

typedef struct s_echo
{
	int				i;
	int				j;
	int				ok;
	int				count_cmd;
}					t_echo;

typedef struct s_export
{
	t_env			*tmp;
	t_env			*element;
	int				count;
	int				i;
	int				var_env;
	char			*compare;
	int				is_ok;
}					t_export;



/*BUILTINS*/

void	builtins(char **cmd, t_shell *shell);

int		cmd_export(char **cmd, t_shell *shell);
void	print_export(t_shell *shell);
void    init_export(t_export *export);




char	**sort_env(char **tab, int size);
char	**env_in_tab(t_shell *shell);
int		check_var_env(t_export *export, t_shell *shell, char **cmd);
int		replace_var_env(t_shell *shell, char *str, t_export *export);


int		cmd_env(char **cmd, t_shell *shell);
int		cmd_cd(char **cmd, t_shell *shell);
int 	new_pwd(t_shell *shell, char *dir);
int		cmd_exit(char **cmd);
int		cmd_pwd(char **cmd, t_shell *shell);


void	count_cmd(t_echo *echo, char **cmd);
void 	init_echo(t_echo *echo);
int		cmd_echo(char **cmd);
void	parse_cmd_n(t_echo *e, char **cmd);
int		cmd_echo2(t_echo *echo, char **cmd);


/*UTILS*/
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcpy_egal(char *dest, char *src);
char	*ft_strcat_mini(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
int     ft_str_is_numeric(char *str);
int     ft_atoi_check(const char *nptr);
int     ft_atoi(const char *nptr);


/*GESTION DE LENV*/

void    ft_view_env(t_env *lst);
void	ft_lstclear_env(t_env *lst);
int		get_home(t_shell *shell);
int		get_old_pwd(t_shell *shell);
int		get_pwd(t_shell *shell);
int		copy_of_env(char **env, t_shell *shell);

t_env	*ft_lstnew_env(void *content);
void	ft_lstadd_back_env(t_env **lst, t_env *new);



#endif