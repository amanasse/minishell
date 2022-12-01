/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:03:50 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/01 11:57:02 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	cmd_env(char **cmd, t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->environ;
	if (cmd[1] == NULL)
		ft_view_env(tmp);
	else
	{
		printf("env: '%s': No such file or directory\n", cmd[1]);
		return (127);
	}
	return (0);
}
