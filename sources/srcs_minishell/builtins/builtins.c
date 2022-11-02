/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:20:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/02 15:30:37 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int		cmd_exit(char **cmd)
{
	if ((ft_strcmp(cmd[0], "exit")) == 0 )
	{
		printf("exit\n");
		// destroy_cmd(cmd);
		return (0);
	}
	return(1);
}

void	cmd_pwd(char **cmd)
{
	char *pwd;

	if ((ft_strcmp(cmd[0], "pwd")) == 0 )
	{
		pwd = getenv("PWD");
		if(cmd[1])
			printf("pwd: too many arguments.\n");		
		else
			printf ("%s\n", pwd);
	}
}

char	*cmd_cd(char **cmd)
{
	int t;
	char *dir;

	t = 0;
	if ((ft_strcmp(cmd[0], "cd")) == 0 )
	{
		if ((ft_strcmp(cmd[1], "~")) == 0) 
		{
			dir = getenv("HOME");
		}	
		else  dir = cmd[1] ;	
		t = chdir(dir);
		if (t == 0) 
		{
			dir = getcwd(NULL, 0);
			opendir(dir);
		}	
		else
			printf("\nError : Directory change failed.\n");
	}
	return (dir);
}

void cmd_echo(char **cmd)
{
	if ((ft_strcmp(cmd[0], "pwd")) == 0 )
	{

		if(cmd[1])
			printf("pwd: too many arguments.\n");		
		else
			printf ("%s\n", pwd);
	}




}
