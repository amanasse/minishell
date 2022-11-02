/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:20:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/02 13:08:27 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

char *change_directory(char **cmd)
{
	int t;
	char *dir;
	char *pwd;

	t = 0;
	if ((ft_strcmp(cmd[0], "cd")) == 0 )
	{
		if ((ft_strcmp(cmd[1], "~")) == 0) 
		{
			dir = getenv("HOME");
		}	
		else  dir = cmd[1] ;	
		printf ("dir = [%s]\n", dir);
		t = chdir(dir);
		printf ("t = [%d]\n", t);
		if (t == 0) 
		{
			dir = getcwd(NULL, 0);
			printf ("dir apres getcwd = [%s]\n", dir);
			opendir(dir);
			pwd = getenv("PWD");
			printf ("pwd = [%s]\n", pwd);

		}	
		else
			printf("\nError : Directory change failed.\n");
	}
	return (dir);
}
