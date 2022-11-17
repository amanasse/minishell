/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:08 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/17 17:01:28 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	cmd_pwd(char **cmd, t_minishell *minishell)
{
	t_env	*tmp;

	if (cmd[1])
	{
		printf("pwd: too many arguments.\n");
		return (1);
	}
	else
	{
		tmp = minishell->environ;
		while (tmp != NULL)
		{
			if (ft_strnstr(tmp->str, "PWD=", 4) == 0)
				printf("%s\n", tmp->str + 4);
			tmp = tmp->next;
		}
		return (0);
	}
}
