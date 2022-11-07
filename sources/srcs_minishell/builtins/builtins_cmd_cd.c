/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:42 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/07 12:11:46 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int new_old_pwd(t_shell *shell, char *dir)
{
	t_env *tmp;
	int i;

	i = ft_strlen(dir + 4);
	tmp = shell->environ;
	while (tmp != NULL)
	{
		if(ft_strnstr(tmp->str, "PWD=", 4) == 0)
		{
			free(tmp->str);
			tmp->str = ft_strncpy(dir, i);
			if (tmp->str = NULL)
				return (-1);			
			tmp = tmp->next;
		}
	}
	return (0);
}

char *go_home(t_env *tmp)
{
	char *dir;
	
	while (tmp != NULL)
	{
		if(ft_strnstr(tmp->str, "HOME=", 5) == 0)
			dir = tmp->str + 5;
		tmp = tmp->next;
	}
	return (dir);
}

int	*cmd_cd(char **cmd, t_shell *shell)
{
	int t;
	int i;
	char *dir;
	t_env	*tmp;

	t = 0;
	i = 0;
	tmp = shell->environ;
	while (cmd[i])
		i++;
	if(i == 1)
		dir = go_home(tmp);
    else if (i == 2 && (ft_strcmp(cmd[1], "~")) == 0)
		dir = go_home(tmp);
	else
		dir = cmd[1];
	t = chdir(dir);
	if (t == 0) 
	{
		dir = getcwd(NULL, 0);
		new_old_pwd(shell, dir);
		printf("dir = %s\n", dir);
		
		free(dir);
	}
	else
		printf("\nError : Directory change failed.\n");
	return (0);
}
