/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:57:06 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/10 16:19:03 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

// int	get_old_pwd(t_shell *shell)
// {
// 	int	i;

// 	i = ft_strlen(shell->environ->str);
// 	shell->old_pwd = malloc(sizeof(char) * i + 1);
// 	if (shell->old_pwd == NULL)
// 		return (-1);
// 	ft_strlcpy(shell->old_pwd, shell->environ->str, i + 1);
// 	shell->environ->str = shell->old_pwd;
// 	return (0);
// }

// int	get_pwd(t_shell *shell)
// {
// 	int	j;

// 	j = ft_strlen(shell->environ->str);
// 	shell->pwd = malloc(sizeof(char) * j + 1);
// 	if (shell->pwd == NULL)
// 		return (-1);
// 	ft_strlcpy(shell->pwd, shell->environ->str, j + 1);
// 	shell->environ->str = shell->pwd;
// 	return (0);
// }

// int	get_home(t_shell *shell)
// {
// 	t_env	*tmp;

// 	tmp = shell->environ;
// 	while (shell->environ != NULL)
// 	{
// 		if (ft_strnstr(shell->environ->str, "OLDPWD=", 7) == 0)
// 		{
// 			if (get_old_pwd(shell) == -1)
// 				return (-1);
// 			break ;
// 		}		
// 		shell->environ = shell->environ->next;
// 	}
// 	shell->environ = tmp;
// 	while (shell->environ != NULL)
// 	{
// 		if (ft_strnstr(shell->environ->str, "PWD=", 4) == 0)
// 		{
// 			if (get_pwd(shell) == -1)
// 				return (-1);
// 		}		
// 		shell->environ = shell->environ->next;
// 	}
// 	shell->environ = tmp;
// 	return (0);
// }

int	copy_of_env(char **env, t_shell *shell)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back_env(&shell->environ, ft_lstnew_env(env[i]));
		i++;
	}
	// if (get_home(shell) == -1)
	// 	return (-1);
	return (0);
}
