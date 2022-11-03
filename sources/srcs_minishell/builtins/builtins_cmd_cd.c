/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:42 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/03 16:53:48 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

char	*cmd_cd(char **cmd, t_env *c_env)
{
	int t;
	char *dir;
    (void) *c_env;

	t = 0;
    if ((ft_strcmp(cmd[1], "~")) == 0) 
		dir = getenv("HOME");
	else  dir = cmd[1] ;	
	t = chdir(dir);
	if (t == 0) 
	{
		dir = getcwd(NULL, 0);
		opendir(dir);
	}	
	else
		printf("\nError : Directory change failed.\n");
	return (dir);
}
