/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:57:06 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/07 16:30:12 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int	get_home(t_shell *shell)
{
	int i;
	int j;
	t_env *tmp;

	i = 0;
	tmp = shell->environ;
	while (shell->environ != NULL)
	{
		if(ft_strnstr(shell->environ->str, "OLDPWD=", 7) == 0)
		{
			i = ft_strlen(shell->environ->str);
			shell->old_pwd = malloc(sizeof(char) * i + 1);
			if(shell->old_pwd == NULL)
				return (-1);
			ft_strlcpy(shell->old_pwd, shell->environ->str, i + 1);
			shell->environ->str = shell->old_pwd;
			shell->environ = tmp;
			break ;
		}		
		shell->environ = shell->environ->next;
	}
	tmp = shell->environ;
	while (shell->environ != NULL)
	{
		if(ft_strnstr(shell->environ->str, "PWD=", 4) == 0)
		{
			j = ft_strlen(shell->environ->str);
			shell->pwd = malloc(sizeof(char) * j + 1);
			if(shell->pwd == NULL)
				return (-1);
			ft_strlcpy(shell->pwd, shell->environ->str, j + 1);
			shell->environ->str = shell->pwd;
			shell->environ = tmp;
			break ;
		}		
		shell->environ = shell->environ->next;
	}
	printf("shell->old_pwd = %s\n", shell->old_pwd);
	printf("shell->pwd = %s\n", shell->pwd);
	return(0);
}


int		copy_of_env(char **env, t_shell *shell)
{
	int	i;
    
    i = 0;
	while (env[i])
	{
		ft_lstadd_back_env(&shell->environ, ft_lstnew_env(env[i]));
		i++;
	}
	if (get_home(shell) == -1)
		return (-1);
	return (0);
}
