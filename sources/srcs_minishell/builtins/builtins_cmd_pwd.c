/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:41:08 by amanasse          #+#    #+#             */
/*   Updated: 2022/11/14 16:02:04 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

int	cmd_pwd(char **cmd, t_shell *shell)
{
	t_env	*tmp;

	if (cmd[1])
	{
		printf("pwd: too many arguments.\n");
		return (1);
	}
	else
	{
		tmp = shell->environ;
		while (tmp != NULL)
		{
			if (ft_strnstr(tmp->str, "PWD=", 4) == 0)
				printf("%s\n", tmp->str + 4);
			tmp = tmp->next;
		}
	}
	return (0);
}
