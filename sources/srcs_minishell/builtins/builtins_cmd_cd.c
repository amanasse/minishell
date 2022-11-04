/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:42 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/04 17:33:41 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

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

int	*cmd_cd(char **cmd, t_env *c_env)
{
	int t;
	int i;
	// int j;
	char *dir;
	t_env	*tmp;

	t = 0;
	i = 0;
	tmp = c_env;
	while (cmd[i])
		i++;
	if(i == 1)
		dir = go_home(tmp);
    else if (i == 2 && (ft_strcmp(cmd[1], "~")) == 0)
		dir = go_home(tmp);
	else
		dir = cmd[1];
	printf("dir = %s\n", dir);
	t = chdir(dir);
	if (t == 0) 
	{
		dir = getcwd(NULL, 0);
		printf("dir = %s\n", dir);
		
		free(dir);
	}
	else
		printf("\nError : Directory change failed.\n");
	return (0);
}
