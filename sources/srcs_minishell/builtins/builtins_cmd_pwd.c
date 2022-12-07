/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:08 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/07 15:18:50 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	cmd_pwd(char **cmd, t_minishell *minishell)
{
	t_env	*tmp;

	(void)cmd;
	tmp = minishell->environ;
	while (tmp != NULL)
	{
		if (ft_strnstr(tmp->str, "PWD=", 4) == 0)
		{	
			printf("%s\n", tmp->str + 4);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}
