/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:08 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/07 11:40:28 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"


void	cmd_pwd(char **cmd, t_shell *shell)
{
	t_env   *tmp;

	if(cmd[1])
		printf("pwd: too many arguments.\n");		
	else
	{
		tmp = shell->environ;
		while (tmp != NULL)
		{
			if(ft_strnstr(tmp->str, "PWD=", 4) == 0)
				printf("%s\n", tmp->str + 4);	
			tmp = tmp->next;
		}
	}
}
